# Stock_Dashboard
Stock Dashboard Using Streamlit in Pyhton

README file for the provided code:

```
# Stock Dashboard

This Stock Dashboard is a web application built using Streamlit, which allows users to analyze stock data, view pricing movements, fundamental data, news, and technical indicators for a given stock ticker.

## Installation

To run this application, make sure you have the following dependencies installed:

- streamlit
- pandas
- numpy
- yfinance
- plotly.express
- plotly.graph_objects
- alpha_vantage
- stocknews
- pandas_ta

You can install these dependencies by running the following command:

```shell
pip install streamlit pandas numpy yfinance plotly alpha_vantage stocknews pandas_ta
```

## Usage

1. Run the application by executing the following command in your terminal:

```shell
streamlit run stock_dashboard.py
```

2. Once the application is running, you will see a sidebar on the left side where you can enter the stock ticker and select the start and end dates for the data.

3. The dashboard consists of several tabs:

   - **Line Chart**: Displays the line chart of the adjusted close prices for the given stock ticker.
   - **Candle Chart**: Displays the candlestick chart for the given stock ticker.
   - **Pricing Data**: Shows the pricing movements, annual return, standard deviation, and risk-adjusted return for the selected stock.
   - **Fundamental Data**: Provides the balance sheet, income statement, and cash flow statement for the selected stock.
   - **Top 10 News**: Displays the top 10 news articles related to the selected stock, including their published date, title, summary, and sentiment.
   - **Technical Analysis**: Allows users to select and view various technical indicators for the selected stock.

4. Uncomment the code related to the OpenAI ChatGPT integration if you have a valid session token for the ChatGPT API. This will provide additional information on reasons to buy/sell the stock and SWOT analysis.



