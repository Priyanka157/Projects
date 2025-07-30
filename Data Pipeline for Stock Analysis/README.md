# Data Pipeline for Financial Analysis

## Overview
A modular ETL data pipeline fetching stock data from Yahoo Finance, processing it, storing in SQLite, and visualizing results.

## Structure

- `src/`: ETL scripts for extraction, transformation, and loading.
- `dags/`: Airflow DAG to orchestrate ETL workflow on schedule.
- `dashboard/`: Streamlit app for visualization.
- `notebooks/`: Jupyter notebook for data exploration.
- `data/`: Stores raw and processed CSV files and SQLite DB.

```
Data pipeline for Financial Analysis/
├── dags/                     
│   └── etl_dag.py                     # Airflow DAG to orchestrate pipeline
├── src/                      
│   ├── extract.py                     # Data extraction script
│   ├── transform.py                   # Data transformation logic
│   └── load.py                        # Load to SQLite DB
├── notebooks/                
│   └── exploratory_analysis.ipynb     # EDA and validation
├── dashboard/               
│   └── dashboard.py                   # Streamlit dashboard
│   └── Screenshot1.png                # Dashboard view
│   └── Screenshot2.png                # Dashboard view
├── data/                           
│   ├── raw/                           # Raw downloaded data CSVs
│   └── processed/                     # Processed CSVs
│   └── financial_data.db              # SQLite Database
│   └── signals_report.csv             # Signals report generated when buy/sell signals are triggered.
├── requirements.txt                   # Python dependencies
└── README.md

```

## How to run

- Install dependencies:

pip install -r requirements.txt

- Start Airflow (example):

airflow webserver

Then access Airflow UI at http://localhost:8080 and trigger the etl_dag DAG.

- Or run ETL manually:

python src/extract.py
python src/transform.py
python src/load.py

- Exploratory Data Analysis

jupyter notebook notebooks/exploratory_analysis.ipynb

- Run the Streamlit dashboard:

streamlit run dashboard/dashboard.py

## Future improvements
- Containerize the pipeline with Docker.
- Add Kafka or Spark streaming for real-time data.
- Deploy on AWS/GCP with managed Airflow and cloud DB services.
