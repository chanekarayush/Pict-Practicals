import streamlit as st
import sqlite3
import pandas as pd
import yfinance as yf
import plotly.express as px
import plotly.graph_objects as go
import numpy as np
from datetime import date
from alpha_vantage.fundamentaldata import FundamentalData
from stocknews import StockNews
import pandas_ta as ta

# Initialize database tables
def init_db():
    conn = sqlite3.connect('trading_app.db')
    cursor = conn.cursor()
    cursor.execute('''
        CREATE TABLE IF NOT EXISTS portfolio (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            ticker TEXT,
            quantity INTEGER,
            buy_price REAL,
            buy_date DATE
        )
    ''')
    cursor.execute('''
        CREATE TABLE IF NOT EXISTS trade_history (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            ticker TEXT,
            quantity INTEGER,
            trade_type TEXT,
            trade_price REAL,
            trade_date DATE DEFAULT CURRENT_DATE
        )
    ''')
    conn.commit()
    conn.close()

# Initialize session state variables
if 'page' not in st.session_state:
    st.session_state.page = "Dashboard"

if 'current_balance' not in st.session_state:
    st.session_state.current_balance = 100000.0  # Example initial balance

# Utility function to reset database tables
def reset_table(table_name):
    conn = sqlite3.connect('trading_app.db')
    cursor = conn.cursor()
    try:
        cursor.execute(f'DELETE FROM {table_name}')
        conn.commit()
        st.success(f"{table_name.capitalize()} reset successfully!")
    except sqlite3.Error as e:
        st.error(f"Database error: {e}")
    finally:
        conn.close()

# Utility function to reset balance
def reset_balance():
    st.session_state.current_balance = 100000.0
    st.success("Balance reset to $100,000!")
    
    
# Utility function to get stock price
def get_stock_price(ticker):
    try:
        data = yf.download(ticker, period='1d')
        return data['Close'].iloc[-1]  # Get the latest closing price
    except Exception:
        return None

# Buy stock and update portfolio
def buy_stock(ticker, quantity):
    current_price = get_stock_price(ticker)
    if current_price is None:
        st.error(f"Failed to fetch price for {ticker}.")
        return

    total_cost = current_price * quantity
    if total_cost.item() > st.session_state.current_balance:
        st.error(f"Insufficient funds! You have ${st.session_state.current_balance:.2f} available.")
        return

    conn = sqlite3.connect('trading_app.db')
    cursor = conn.cursor()
    try:
        cursor.execute('''
            INSERT INTO portfolio (ticker, quantity, buy_price, buy_date)
            VALUES (?, ?, ?, ?)
        ''', (ticker, quantity, current_price, date.today()))
        cursor.execute('''
            INSERT INTO trade_history (ticker, quantity, trade_type, trade_price)
            VALUES (?, ?, 'BUY', ?)
        ''', (ticker, quantity, current_price))
        conn.commit()

        # Update balance
        st.session_state.current_balance -= total_cost
        st.success(f"Bought {quantity} shares of {ticker} at ${current_price:.2f} each.")
    except sqlite3.Error as e:
        st.error(f"Database error: {e}")
    finally:
        conn.close()

# Sell stock and update portfolio
def sell_stock(ticker, quantity):
    current_price = get_stock_price(ticker)
    if current_price is None:
        st.error(f"Failed to fetch price for {ticker}.")
        return

    conn = sqlite3.connect('trading_app.db')
    cursor = conn.cursor()
    try:
        cursor.execute('SELECT * FROM portfolio WHERE ticker = ?', (ticker,))
        portfolio_data = cursor.fetchall()

        total_shares_owned = sum(row[2] for row in portfolio_data)
        if total_shares_owned < quantity:
            st.error("You do not have enough shares to sell.")
            return

        shares_sold = 0
        for row in portfolio_data:
            remaining = quantity - shares_sold
            if remaining == 0:
                break

            owned_shares = row[2]
            if owned_shares <= remaining:
                st.session_state.current_balance += owned_shares * current_price
                cursor.execute('DELETE FROM portfolio WHERE id = ?', (row[0],))
                shares_sold += owned_shares
            else:
                st.session_state.current_balance += remaining * current_price
                cursor.execute('UPDATE portfolio SET quantity = quantity - ? WHERE id = ?', (remaining, row[0]))
                shares_sold += remaining

        cursor.execute('''
            INSERT INTO trade_history (ticker, quantity, trade_type, trade_price)
            VALUES (?, ?, 'SELL', ?)
        ''', (ticker, quantity, current_price))
        conn.commit()
        st.success(f"Sold {quantity} shares of {ticker} at ${current_price:.2f} each.")
    except sqlite3.Error as e:
        st.error(f"Database error: {e}")
    finally:
        conn.close()

# View portfolio
def view_portfolio():
    conn = sqlite3.connect('trading_app.db')
    cursor = conn.cursor()
    portfolio_data = cursor.execute('SELECT * FROM portfolio').fetchall()
    conn.close()

    if not portfolio_data:
        st.info("Your portfolio is empty.")
        return

    portfolio_df = pd.DataFrame(portfolio_data, columns=['ID', 'Ticker', 'Quantity', 'Buy Price', 'Buy Date'])
    portfolio_df['Current Price'] = portfolio_df['Ticker'].apply(get_stock_price)
    portfolio_df['Profit/Loss'] = (portfolio_df['Current Price'] - portfolio_df['Buy Price']) * portfolio_df['Quantity']

    st.write(f"**Available Balance:** ${st.session_state.current_balance:.2f}")
    st.write(portfolio_df[['Ticker', 'Quantity', 'Buy Price', 'Current Price', 'Profit/Loss']])

    total_pl = portfolio_df['Profit/Loss'].sum()
    st.write(f"**Total Portfolio P/L:** ${total_pl:.2f}")

# View trade history
def view_trade_history():
    conn = sqlite3.connect('trading_app.db')
    cursor = conn.cursor()
    trade_history_data = cursor.execute('SELECT * FROM trade_history').fetchall()
    conn.close()

    if not trade_history_data:
        st.info("No trade history available.")
        return

    trade_history_df = pd.DataFrame(trade_history_data, columns=['ID', 'Ticker', 'Quantity', 'Trade Type', 'Trade Price', 'Trade Date'])
    st.write(trade_history_df[['Ticker', 'Quantity', 'Trade Type', 'Trade Price', 'Trade Date']])

def add_to_watchlist(ticker):
    conn = sqlite3.connect('watchlist.db')
    cursor = conn.cursor()
    try:
        cursor.execute('INSERT INTO watchlist (ticker) VALUES (?)', (ticker,))
        if cursor.fetchone():
            st.info(f'{ticker} is already in your watchlist!')
        else:
            # Insert the ticker if it doesn't exist
            cursor.execute('INSERT INTO watchlist (ticker) VALUES (?)', (ticker,))
            conn.commit()
            st.success(f'Successfully added {ticker} to the watchlist!')
    except sqlite3.Error as e:
        st.error(f'Error adding {ticker} to the watchlist: {e}')
    finally:
        conn.close()

def remove_from_watchlist(ticker):
    conn = sqlite3.connect('watchlist.db')
    cursor = conn.cursor()
    try:
        cursor.execute('DELETE FROM watchlist WHERE ticker = ?', (ticker,))
        conn.commit()
        st.success(f'Successfully removed {ticker} from the watchlist!')
    except sqlite3.Error as e:
        st.error(f'Error removing {ticker} from the watchlist: {e}')
    finally:
        conn.close()
        
def load_watchlist():
    conn = sqlite3.connect('watchlist.db')
    cursor = conn.cursor()
    watchlist_data = cursor.execute('SELECT ticker FROM watchlist').fetchall()
    watchlist_with_price = []
    for row in watchlist_data:
        ticker = row[0]
        try:
            data = yf.download(ticker, period='1d')
            data.head()
            if data.empty:
                st.warning(f"Skipping {ticker} as stock has been delisted or removed.")
                cursor.execute("DELETE FROM watchlist WHERE ticker = ?", (ticker,))
                conn.commit()
                continue
            current_price = data['Close'].iloc[-1]
            watchlist_with_price.append((ticker, current_price))
        except Exception as e:
            st.error(f"Error fetching current price for {ticker}: {e}")
    conn.close()
    return watchlist_with_price
# Initialize database
init_db()

# Navigation
col1, col2, col3, col4 = st.columns(4)
with col1:
    if st.button("Dashboard"):
        st.session_state.page = "Dashboard"
with col2:
    if st.button("Portfolio"):
        st.session_state.page = "Portfolio"
with col3:
    if st.button("Trade History"):
        st.session_state.page = "Trade History"
with col4:
    if st.button("Watchlist"):
        st.session_state.page = "Watchlist"
        
        
# Page content
if st.session_state.page == "Dashboard":
    st.title("Stock Dashboard")
    ticker_input = st.sidebar.text_input("Enter Ticker Symbol")
    start_date = st.sidebar.date_input('Start Date', value=date(2020, 1, 1))
    end_date = st.sidebar.date_input('End Date', value=date.today())
    quantity = st.sidebar.number_input("Quantity", min_value=1, step=1)

    if st.sidebar.button("Buy Stock"):
        buy_stock(ticker_input, quantity)

    if st.sidebar.button("Sell Stock"):
        sell_stock(ticker_input, quantity)
    if ticker_input:
        # Fetch the stock data
        data = yf.download(ticker_input, start=start_date, end=end_date)

        # Create tabs for displaying charts
        line_chart, candle_chart = st.tabs(["Line Chart", "Candle Chart"])
        
        with line_chart:
            st.header('Line Chart')
            print(data.columns)
            fig = px.line(data, x=data.index, y=data[('Close', ticker_input)].squeeze(), title=ticker_input)
            st.plotly_chart(fig)
        
        with candle_chart:
            st.header('Candle Chart')
            fig = go.Figure(data=[go.Candlestick(
                x=data.index, 
                open=data[('Open', ticker_input)], 
                high=data[('High', ticker_input)], 
                low=data[('Low', ticker_input)], 
                close=data[('Close', ticker_input)],
            )])
            st.plotly_chart(fig)


        # Create additional tabs for other sections
        pricing_data, fundamental_data, news, tech_indicator = st.tabs(["Pricing Data",
                                                                        "Fundamental Data",
                                                                        "News",
                                                                        "Technical Indicator"])

        with pricing_data:
            st.header('Pricing Movements')
            data2 = data.copy()
            data2['% Change'] = data['Close'] / data['Close'].shift(1) - 1
            st.write(data2)
            annual_return = data2['% Change'].mean() * 252 * 100
            st.write('Annual Return is ', annual_return, '%')
            stdev = np.std(data2['% Change']) * np.sqrt(252) * 100
            st.write('Standard Deviation is', stdev, '%')
            st.write('Risk Adj. Return is', annual_return / stdev)

        with fundamental_data:
            st.header('Fundamental Data')
            key = '86N58O1FO8EH1EQN'
            fd = FundamentalData(key, output_format='pandas')
            balance_sheet = fd.get_balance_sheet_annual(ticker_input)[0]
            bs = balance_sheet.T[2:]
            bs.columns = list(balance_sheet.T.iloc[0])
            st.write(bs)

        with news:
            st.header(f'News of {ticker_input}')
            sn = StockNews(ticker_input, save_news=False)
            df_news = sn.read_rss()
            for i in range(10):
                st.subheader(f'News {i+1}')
                st.write(df_news['published'][i])
                st.write(df_news['title'][i])
                st.write(df_news['summary'][i])
                title_sentiment = df_news['sentiment_title'][i]
                st.write(f'Title Sentiment {title_sentiment}')
                news_sentiment = df_news['sentiment_summary'][i]
                st.write(f'News Sentiment {news_sentiment}')

        with tech_indicator:
            st.subheader('Technical Analysis Dashboard')
            if data.isnull().sum().sum() > 0:
                st.warning("Warning: Data contains missing values. Filling missing values.")
                data.fillna(method='ffill', inplace=True)  # Handle missing values
            try:
                method = 'sma'
                df = pd.DataFrame()
                ind_list = df.ta.indicators(as_list=True) if not df.empty else []
            
                if not ind_list:
                    st.error("No indicators found!")
                else:
                    technical_indicator = st.selectbox('Tech Indicator', options=ind_list)
                    method = technical_indicator if hasattr(ta, technical_indicator) else 'sma'

            
                indicator = pd.DataFrame(getattr(ta, method)(low=data['Low'], close=data['Close'], high=data['High'], volume=data['Volume']))
                indicator['Close'] = data['Close']         
                # Display indicator
                figw_ind_new = px.line(indicator)
                st.plotly_chart(figw_ind_new)
                st.write(indicator)
            except Exception as e:
                st.error(f"Error in Calculating the Indicator: {e}")



  

elif st.session_state.page == "Portfolio":
    st.title("Portfolio")
    st.subheader(f"Available Balance: ${st.session_state.current_balance:.2f}")
    view_portfolio()
    if st.button("Reset Portfolio"):
        reset_table('portfolio')
        reset_balance()

elif st.session_state.page == "Trade History":
    st.title("Trade History")
    
    view_trade_history()
    if st.button("Reset Trade History"):
        reset_table('trade_history')




elif st.session_state.page == "Watchlist":
    st.title("My Watchlist")
    
    # Load watchlist data
    watchlist_data = load_watchlist()
    
    if watchlist_data:
        # Create a table-like display with headers
        col1, col2, col3 = st.columns([2, 2, 1])
        col1.subheader("Stock Name")
        col2.subheader("Stock Price")
        col3.subheader("Remove")
        
        # Display each stock in the watchlist
        for index, (ticker, price) in enumerate(watchlist_data):
            col1, col2, col3 = st.columns([2, 2, 1])
            with col1:
                st.write(ticker)
            with col2:
                st.write(price)
            with col3:
                if st.button(f"Remove", key=f"remove_{ticker}"):
                    remove_from_watchlist(ticker)
                    st.experimental_rerun()
    else:
        st.info("Your watchlist is empty.")
    
    # Input to add a ticker to the watchlist
    ticker_to_add = st.text_input("Add a Ticker to Watchlist")
    if st.button("Add to Watchlist"):
        if ticker_to_add:
            add_to_watchlist(ticker_to_add)
            st.rerun()
        else:
            st.error("Please enter a ticker to add.")

    
    if st.button("Reset Watchlist"):
        reset_table('watchlist')
