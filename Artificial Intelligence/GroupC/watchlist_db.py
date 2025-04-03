import sqlite3

# Create a connection to the SQLite database
conn = sqlite3.connect('watchlist.db')
cursor = conn.cursor()

# Create a table to store watchlist
cursor.execute ('''
    CREATE TABLE IF NOT EXISTS watchlist (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        ticker TEXT NOT NULL,
        added_date DATE DEFAULT CURRENT_DATE
    )''')


# Commit and close the connection
conn.commit()
conn.close()
