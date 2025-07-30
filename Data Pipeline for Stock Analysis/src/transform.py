import pandas as pd
import os
import logging

logging.basicConfig(level=logging.INFO, format='%(asctime)s %(levelname)s:%(message)s')

def transform_data(ticker="AAPL", input_dir="../data/raw", output_dir="../data/processed"):
    file_path = os.path.join(input_dir, f"{ticker}_raw.csv")
    logging.info(f"Reading raw data from {file_path}")

    try:
        df = pd.read_csv(file_path)
    except FileNotFoundError:
        logging.error(f"Raw data file not found for ticker {ticker}.")
        return

    # Check what columns are present
    logging.info(f"Available columns: {list(df.columns)}")

    # If 'Date' is a column, parse it. If it's the index, reset.
    if "Date" in df.columns:
        df["Date"] = pd.to_datetime(df["Date"])
    else:
        df.reset_index(inplace=True)
        df["Date"] = pd.to_datetime(df["Date"])

    # Drop 'Ticker' column if it's there
    if "Ticker" in df.columns:
        df.drop(columns=["Ticker"], inplace=True)

    # Make sure these columns exist before trying to convert them
    cols_to_numeric = [col for col in ["Open", "High", "Low", "Close", "Adj Close", "Volume"] if col in df.columns]
    for col in cols_to_numeric:
        df[col] = pd.to_numeric(df[col], errors="coerce")

    # Drop rows where Close is NaN (can't calculate anything)
    df = df.dropna(subset=["Close"])

    # Add technical indicators
    df["MA_7"] = df["Close"].rolling(window=7).mean()
    df["MA_30"] = df["Close"].rolling(window=30).mean()

    # Volatility only if Open, High, Low exist
    if all(c in df.columns for c in ["Open", "High", "Low"]):
        df["Volatility"] = (df["High"] - df["Low"]) / df["Open"]

    # Save
    os.makedirs(output_dir, exist_ok=True)
    processed_path = os.path.join(output_dir, f"{ticker}_processed.csv")
    df.to_csv(processed_path, index=False)
    logging.info(f"Saved processed data to {processed_path}")

if __name__ == "__main__":
    transform_data()
