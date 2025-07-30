from airflow import DAG
from airflow.operators.python import PythonOperator
from datetime import datetime, timedelta
import sys
import os

# Add src folder to sys.path so Airflow can import the ETL functions
sys.path.insert(0, os.path.abspath(os.path.join(os.path.dirname(__file__), '../src')))

from extract import fetch_stock_data
from transform import transform_data
from load import load_to_sqlite

default_args = {
    "owner": "airflow",
    "start_date": datetime(2025, 1, 1),
    "retries": 1,
    "retry_delay": timedelta(minutes=5),
}

with DAG(
    dag_id="etl_dag",
    default_args=default_args,
    schedule_interval=None,  #"@daily"
    catchup=False,
    max_active_runs=1,
) as dag:

    extract_task = PythonOperator(
        task_id="extract_stock_data",
        python_callable=fetch_stock_data,
        op_kwargs={"ticker": "AAPL"},
    )

    transform_task = PythonOperator(
        task_id="transform_stock_data",
        python_callable=transform_data,
        op_kwargs={"ticker": "AAPL"},
    )

    load_task = PythonOperator(
        task_id="load_stock_data",
        python_callable=load_to_sqlite,
        op_kwargs={"ticker": "AAPL"},
    )

    extract_task >> transform_task >> load_task
