import yfinance as yf
import pandas as pd
import os
import logging
from datetime import datetime

logging.basicConfig(level=logging.INFO, format='%(asctime)s %(levelname)s:%(message)s')

def fetch_stock_data(ticker="AAPL", start_date="2022-01-01", end_date=None, output_dir="../data/raw"):
    if end_date is None:
        end_date = datetime.today().strftime('%Y-%m-%d')
    logging.info(f"Fetching data for {ticker} from {start_date} to {end_date}")
    
    try:
        df = yf.download(ticker, start=start_date, end=end_date)
        if df.empty:
            logging.warning(f"No data fetched for {ticker}.")
            return
        df.reset_index(inplace=True)
        os.makedirs(output_dir, exist_ok=True)
        file_path = os.path.join(output_dir, f"{ticker}_raw.csv")
        df.to_csv(file_path, index=False)
        logging.info(f"Saved raw data to {file_path}")
    except Exception as e:
        logging.error(f"Error fetching data: {e}")

if __name__ == "__main__":
    fetch_stock_data()
