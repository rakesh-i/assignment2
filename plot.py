import os, glob
import pandas as pd
import plotly.express as px
import plotly.graph_objects as go
import numpy as np

script_dir = os.path.dirname(os.path.abspath(__file__))

csv_files = glob.glob(os.path.join(script_dir, "Algo*_*.csv"))
csv_files += glob.glob(os.path.join(script_dir, "Algo*_*.CSV"))

print("Found CSVs:", csv_files)

algo_names = {
    1: "Bubble Sort",
    2: "Insertion Sort",
    3: "Merge Sort",
    4: "Heap Sort",
    5: "Radix Sort",
    6: "QuickSort (first pivot)",
    7: "QuickSort (random pivot)",
    8: "QuickSort (median pivot)"
}

# Load data
data = {}
for file in csv_files:
    base = os.path.basename(file)
    algo_str, arr_str = base.replace(".csv", "").split("_")
    algo_id = int(algo_str.replace("Algo", ""))
    arr_type = arr_str

    df = pd.read_csv(file)
    if algo_id not in data:
        data[algo_id] = {}
    data[algo_id][arr_type] = df



def comparison_counts(algo_name, n):
    if algo_name == "Bubble Sort":
        best = n - 1
        avg = n*(n-1)/2  
        worst = n*(n-1)/2
    elif algo_name == "Insertion Sort":
        best = (n - 1)
        avg = (n**2 + 3*n - 4) / 4   
        worst = n*(n-1)/2
    elif algo_name == "Merge Sort":
        best = avg = worst = n*np.log2(n)*10**2
    elif algo_name == "Heap Sort":
        best = avg = worst = n*np.log2(n)*10**2
    elif algo_name == "Radix Sort":
        k = np.log10(n)
        best = avg = worst = n * k*10**2
    elif algo_name in ["QuickSort (last pivot)", "QuickSort (first pivot)"]:
        best = (n*np.log2(n)-n+1)*10**2
        avg = (2*(n+1)*(np.log(n)+0.5772) - 4*n)*10**2   
        worst = n*(n-1)/2
    elif algo_name == "QuickSort (random pivot)":
        best = (n*np.log2(n)-n+1)*10**2
        avg = (2*(n+1)*(np.log(n)+0.5772) - 4*n)*10**2   
        worst = n*(n-1)/2
    else:
        best = avg = worst = n
    return best, avg, worst


ARRAY_TYPE_COLORS = {
    "Random": "#e5ff00",    
    "Sorted": "#00ff00",    
    "Reversed": "#ff0000",  
}

def color_for_array_type(arr_type: str) -> str:
    return ARRAY_TYPE_COLORS.get(arr_type, "#7f7f7f")

ALGO_COLORS = {
    "Bubble Sort": "#e0317a",
    "Insertion Sort": "#ff7f0e",
    "Merge Sort": "#2ca02c",
    "Heap Sort": "#a200ff",
    "Radix Sort": "#0011ff",
    "QuickSort (first pivot)": "#b47467",
    "QuickSort (random pivot)": "#00eeff",
    "QuickSort (median pivot)": "#3a3939",
}

def color_for_algo(algo_id: int) -> str:
    return ALGO_COLORS.get(algo_names[algo_id], "#17becf")


BASE_FONT_FAMILY = "Arial"
BASE_FONT_SIZE = 20
LEGEND_FONT_SIZE = 20
AXIS_TITLE_SIZE = 20
TICK_FONT_SIZE = 20
TITLE_FONT_SIZE = 24

def apply_styling(fig, plot_title):
    fig.update_layout(
        title=dict(text=plot_title, font=dict(size=TITLE_FONT_SIZE, family=BASE_FONT_FAMILY)),
        template="plotly_white",
        font=dict(family=BASE_FONT_FAMILY, size=BASE_FONT_SIZE),
        legend=dict(
            orientation="h",       
            yanchor="top",          
            y=-0.15,               
            xanchor="center",       
            x=0.5,                  
            font=dict(size=LEGEND_FONT_SIZE),
            itemsizing="trace"
        )
    )
    fig.update_xaxes(
        title_font=dict(size=AXIS_TITLE_SIZE, family=BASE_FONT_FAMILY),
        tickfont=dict(size=TICK_FONT_SIZE, family=BASE_FONT_FAMILY)
    )
    fig.update_yaxes(
        title_font=dict(size=AXIS_TITLE_SIZE, family=BASE_FONT_FAMILY),
        tickfont=dict(size=TICK_FONT_SIZE, family=BASE_FONT_FAMILY)
    )
    return fig



# --- Plot 1: Compare algorithms for each array type ---
array_types = ["Random", "Sorted", "Reversed"]

for arr_type in array_types:
    fig = go.Figure()
    for algo_id, arrs in data.items():
        if arr_type in arrs:
            df = arrs[arr_type]
            fig.add_trace(go.Scatter(
                x=df["InputSize"],
                y=df["Time(us)"],
                mode='lines+markers',
                name=algo_names[algo_id],
                line=dict(color=color_for_algo(algo_id)),
                marker=dict(color=color_for_algo(algo_id))
            ))
    fig.update_layout(
        xaxis_title="Input Size (n)",
        yaxis_title="Time (μs)"
    )
    fig = apply_styling(fig, f"Sorting Algorithms on {arr_type} Arrays")
    fig.show()


# --- Plot 2: Compare array types for each algorithm ---
for algo_id, arrs in data.items():
    fig = go.Figure()

    for arr_type, df in arrs.items():
        fig.add_trace(go.Scatter(
            x=df["InputSize"],
            y=df["Time(us)"],
            mode='lines+markers',
            name=arr_type,
            line=dict(color=color_for_array_type(arr_type)),
            marker=dict(color=color_for_array_type(arr_type))
        ))
    
    all_n_vals = sorted(set().union(*[df["InputSize"].values for df in arrs.values()]))
    all_n_vals = np.array(all_n_vals, dtype=int)

    best, avg, worst = zip(*[comparison_counts(algo_names[algo_id], n) for n in all_n_vals])
    best = np.array(best, dtype=float)
    avg  = np.array(avg, dtype=float)
    worst= np.array(worst, dtype=float)

    best_time_per_comp  = (10**(-4)) * best
    avg_time_per_comp   = (10**(-4)) * avg
    worst_time_per_comp = (10**(-4)) * worst

    fig.add_trace(go.Scatter(
        x=all_n_vals, y=best_time_per_comp,
        mode="lines",
        name="Theoretical Best-case",
        line=dict(dash="dot", color="black")
    ))
    fig.add_trace(go.Scatter(
        x=all_n_vals, y=avg_time_per_comp,
        mode="lines",
        name="Theoretical Avg-case",
        line=dict(dash="dash", color="black")
    ))
    fig.add_trace(go.Scatter(
        x=all_n_vals, y=worst_time_per_comp,
        mode="lines",
        name="Theoretical Worst-case",
        line=dict(dash="longdash", color="black")
    ))

    fig.update_layout(
        xaxis_title="Input Size (n)",
        yaxis_title="Time (μs)"
    )
    fig = apply_styling(fig, f"{algo_names.get(algo_id, f'Algo {algo_id}')}")
    fig.show()
