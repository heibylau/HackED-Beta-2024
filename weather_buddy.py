import dash
from dash import dcc, html, Input, Output
import plotly.graph_objects as go
import pandas as pd
from datetime import datetime
import boto3

# Fetch data from AWS Timestream
def fetch_data():
    client = boto3.client('timestream-query')

    query = """
    SELECT time, temperature, humidity FROM "esp8266DB"."default"
    ORDER BY time DESC
    LIMIT 6000
    """

    # Execute the query
    response = client.query(QueryString=query)

    # Extract records from query response
    records = response.get('Rows', [])
    
    data = []
    for record in records:
        row = {}
        timestamp = record['Data'][0]['ScalarValue']
        
        # Trim nanoseconds part and keep up to microseconds (6 digits)
        timestamp = timestamp.split('.')[0]  # Trims after microseconds
        row['timestamp'] = datetime.strptime(timestamp, '%Y-%m-%d %H:%M:%S')  
        row['timestamp'] = row['timestamp'] - pd.Timedelta(hours=7) # Convert UTC to MST

        row['temperature'] = float(record['Data'][1]['ScalarValue'])  
        row['humidity'] = float(record['Data'][2]['ScalarValue'])  
        
        data.append(row)
    
    df = pd.DataFrame(data)
    
    return df

# Initialize the app
app = dash.Dash(__name__)
app.css.append_css({"external_url": "/assets/styles.css"})
app.server.static_folder = "assets"

df = fetch_data()

# Layout of the dashboard
app.layout = html.Div([
    html.Title('Weather Buddy'),
    html.H1('Weather Buddy Dashboard', style={'textAlign': 'center'}),

    dcc.Interval(id='interval-component', interval=10000, n_intervals=0),  # Refreshes page every 10 seconds

    # Half-Donut Gauges
    html.Div([
        dcc.Graph(id='temp-gauge'),
        dcc.Graph(id='humidity-gauge')
    ], style={'display': 'flex', 'justify-content': 'space-around'}),

    # Line chart for humidity and temperature over time
    html.Div([
        dcc.Graph(id='line-chart')
    ]),

    # Color-Blind Mode Toggle Button and Dropdown
    html.Div([
        dcc.Dropdown(
            id='color-mode',
            options=[
                {'label': 'Normal', 'value': 'normal'},
                {'label': 'Protanopia', 'value': 'protanopia'},
                {'label': 'Deuteranopia', 'value': 'deuteranopia'},
                {'label': 'Tritanopia', 'value': 'tritanopia'},
            ],
            value='normal',
            style={'display': 'none', 'position': 'fixed', 'top': '70px', 'left': '10px', 'width': '150px'}
        ),
        html.Button('👁️', id='color-blind-toggle', title="Color Blind Mode", style={
            'position': 'fixed',
            'top': '10px',
            'left': '10px',
            'border-radius': '50%',
            'width': '50px',
            'height': '50px',
            'font-size': '20px'
        })
    ])
])

# Callback to update gauges and line chart
@app.callback(
    [Output('temp-gauge', 'figure'), Output('humidity-gauge', 'figure'), Output('line-chart', 'figure')],
    [Input('interval-component', 'n_intervals'), Input('color-mode', 'value')]  # Adding interval as an input
)

def update_dashboard(n_intervals, color_mode):
    df = fetch_data()

    color_schemes = {
        'normal': {'temperature': '#ff4e33', 'humidity': '#004cff'},
        'protanopia': {'temperature': '#9f8e44', 'humidity': '#0161c8'},
        'deuteranopia': {'temperature': '#b48722', 'humidity': '#0165aa'},
        'tritanopia': {'temperature': '#fd4a4c', 'humidity': '#036c71'}
    }
    colors = color_schemes.get(color_mode, color_schemes['normal'])
    
    temp_gauge = go.Figure(go.Indicator(
        mode="gauge+number",
        value=df['temperature'].iloc[0],
        title={'text': "Temperature (°C)"},
        gauge={'axis': {'range': [None, 100]},
               'bar': {'color': colors['temperature']}}
    ))
    temp_gauge.update_layout(paper_bgcolor="#94cbec")

    humidity_gauge = go.Figure(go.Indicator(
        mode="gauge+number",
        value=df['humidity'].iloc[0],
        title={'text': "Humidity (%)"},
        gauge={'axis': {'range': [None, 100]},
               'bar': {'color': colors['humidity']}},
    ))
    humidity_gauge.update_layout(paper_bgcolor="#94cbec")

    line_chart = go.Figure()
    line_chart.add_trace(go.Scatter(
        x=df['timestamp'],
        y=df['temperature'],
        mode='lines',
        name='Temperature',
        line=dict(color=colors['temperature'])
    ))
    line_chart.add_trace(go.Scatter(
        x=df['timestamp'],
        y=df['humidity'],
        mode='lines',
        name='Humidity',
        line=dict(color=colors['humidity'])
    ))
    line_chart.update_layout(title='Temperature and Humidity Over Time', xaxis_title='Time', yaxis_title='Value', paper_bgcolor="#94cbec")

    return temp_gauge, humidity_gauge, line_chart


# Callback to toggle the display of the dropdown menu
@app.callback(
    Output('color-mode', 'style'),
    Input('color-blind-toggle', 'n_clicks')
)
def toggle_color_mode_dropdown(n_clicks):
    if n_clicks and n_clicks % 2 == 1:
        # Show the dropdown
        return {'display': 'block', 'position': 'fixed', 'top': '70px', 'left': '10px', 'width': '150px', 'zIndex': '1000'}
    # Hide the dropdown if button clicked again
    return {'display': 'none'}


# Run the app
if __name__ == '__main__':
    app.run_server(debug=True)
