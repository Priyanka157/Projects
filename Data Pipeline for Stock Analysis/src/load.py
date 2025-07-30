import pandas as pd
import sqlite3
import os
import logging
from datetime import datetime

logging.basicConfig(level=logging.INFO, format="%(asctime)s %(levelname)s:%(message)s")

def load_to_sqlite(ticker="AAPL", input_dir="../data/processed", db_path="../data/financial_data.db"):
    file_path = os.path.join(input_dir, f"{ticker}_processed.csv")
    logging.info(f"Reading processed data from {file_path}")

    try:
        df = pd.read_csv(file_path)
    except FileNotFoundError:
        logging.error(f"Processed file not found for ticker {ticker}.")
        return

    df["Ticker"] = ticker
    df["load_timestamp"] = datetime.now().isoformat()

    conn = sqlite3.connect(db_path)
    cursor = conn.cursor()

    logging.info("Creating table if it doesn't exist...")

    cursor.execute("""
        CREATE TABLE IF NOT EXISTS stock_data (
            Date TEXT NOT NULL,
            Open REAL,
            High REAL,
            Low REAL,
            Close REAL,
            Volume INTEGER,
            MA_7 REAL,
            MA_30 REAL,
            Volatility REAL,
            Ticker TEXT NOT NULL,
            load_timestamp TEXT,
            PRIMARY KEY (Date, Ticker)
        )
    """)

    # Indexes for performance
    cursor.execute("CREATE INDEX IF NOT EXISTS idx_ticker ON stock_data (Ticker);")
    cursor.execute("CREATE INDEX IF NOT EXISTS idx_date ON stock_data (Date);")
    cursor.execute("CREATE INDEX IF NOT EXISTS idx_volatility ON stock_data (Volatility);")

    # Load with conflict handling (ignore duplicates)
    df.to_sql("stock_data", conn, if_exists="append", index=False, method="multi")

    logging.info(f"Loaded data into SQLite DB at {db_path}")
    conn.commit()
    conn.close()

if __name__ == "__main__":
    load_to_sqlite()
