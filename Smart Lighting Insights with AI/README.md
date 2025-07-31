# 💡 Smart Lighting Insights & Optimization Using AI

This project demonstrates how AI and data analytics can be used to analyze and optimize smart lighting systems in commercial buildings using real-world IoT energy data. By exploring lighting patterns, training predictive models, and creating a dynamic dashboard, this project provides actionable insights that could help in reducing energy consumption and improving efficiency.

## 📌 Project Overview

Modern buildings are increasingly adopting smart sensors and IoT systems to monitor energy usage. This project focuses on **analyzing lighting usage data** collected from different zones of a smart building, then using **machine learning** to predict future consumption patterns and finally visualizing these insights in an interactive **Streamlit dashboard**.

## 🚀 Key Features

- 📊 **Data Cleaning & EDA** on lighting and plug load data
- 🧠 **Machine Learning** (Random Forest) to predict lighting usage on time features
- 📈 **Visualizations** of usage patterns and ML performance
- 🌐 **Interactive Streamlit Dashboard** to monitor and explore energy insights
- 🧪 **Modular Notebook** workflow from loading to deployment

## 🧠 Skills Demonstrated

- Data wrangling & time-series processing
- Feature engineering (time-based features)
- Model training, evaluation (R², MSE), and prediction
- Visualization of multi-zone energy patterns
- Building and deploying an interactive dashboard
- Clean, modular, GitHub-ready project organization

## 🛠️ Tools & Technologies Used

- **Python** 🐍 – Core language
- **Pandas & NumPy** – Data manipulation
- **Matplotlib & Seaborn** – Data visualization
- **Scikit-learn** – Machine learning modeling
- **Streamlit** – Web dashboard interface
- **Jupyter Notebook** – Development and experimentation

## 📁 Project Structure
```
Smart Lighting Insights with AI/
│
├── Smart_Lighting_Optimization_AI.ipynb # Jupyter notebook (EDA + ML)
├── Lighting_dashboard.py                # Streamlit dashboard
├── 2019Floor1.7z                        # Raw dataset
├── Dashboard_screenshot                 # Preview of dashboard
├── requirements.txt                     # Python dependencies
└── README.md                            # Project overview
```

## 🛠️ Installation & Usage

- Clone the repository

git clone this-repository

Change directory to this-repository

- Install dependencies

pip install -r requirements.txt

- Run the notebook

jupyter notebook Smart_Lighting_Optimization_AI.ipynb

- Launch the Streamlit app

streamlit run Lighting_dashboard.py

## ✨ Future Improvements
- Add model for plug load
- Integrate Lux sensors if data becomes available
- Real-time deployment with live data feed
