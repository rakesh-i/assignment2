import os, glob
import pandas as pd
import plotly.graph_objects as go

script_dir = os.path.dirname(os.path.abspath(__file__))

csv_files = glob.glob(os.path.join(script_dir, "Algo*_*.csv")) + glob.glob(os.path.join(script_dir, "Algo*_*.CSV"))

print("Found CSVs:", csv_files)

algo_names = {
    1: "Bubble Sort",
    2: "Insertion Sort",
    3: "Merge Sort",
    4: "Heap Sort",
    5: "Radix Sort",
    6: "QuickSort (last pivot)",
    7: "QuickSort (first pivot)",
    8: "QuickSort (random pivot)"
}

array_types = ["Random", "Sorted", "Reversed"]
dash_map = {
    "Random": "solid",
    "Sorted": "dash",
    "Reversed": "dot"
}

algo_colors = {
    1: "#1f77b4",
    2: "#ff7f0e",
    3: "#2ca02c",
    4: "#d62728",
    5: "#9467bd",
    6: "#8c564b",
    7: "#e377c2",
    8: "#7f7f7f",
}

records = []
for file in csv_files:
    base = os.path.basename(file)
    stem = os.path.splitext(base)[0]

    algo_str, arr_str = stem.split("_", 1)
    algo_id = int(algo_str.replace("Algo", ""))
    arr_type = arr_str

    df = pd.read_csv(file)

    cols = {c.lower().strip(): c for c in df.columns}

    xcol = "InputSize" if "inputsize" in cols else [c for c in df.columns if c.lower().strip() in ("n","size","inputsize")][0]
    ycol = "Time(us)" if "time(us)" in cols else [c for c in df.columns if "time" in c.lower()][0]

    records.append({
        "algo_id": algo_id,
        "algo_name": algo_names.get(algo_id, f"Algo {algo_id}"),
        "arr_type": arr_type,
        "df": df.rename(columns={xcol: "InputSize", ycol: "Time(us)"})
    })


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
            y=-0.25,
            xanchor="center",
            x=0.5,
            font=dict(size=LEGEND_FONT_SIZE),
            itemsizing="trace"
        ),
        margin=dict(t=70, b=120, l=80, r=30),
        hovermode="x unified"
    )
    fig.update_xaxes(
        title_font=dict(size=AXIS_TITLE_SIZE, family=BASE_FONT_FAMILY),
        tickfont=dict(size=TICK_FONT_SIZE, family=BASE_FONT_FAMILY),
        title_text="Input Size (n)"
    )
    fig.update_yaxes(
        title_font=dict(size=AXIS_TITLE_SIZE, family=BASE_FONT_FAMILY),
        tickfont=dict(size=TICK_FONT_SIZE, family=BASE_FONT_FAMILY),
        title_text="Time (μs)"
    )
    return fig

fig = go.Figure()

for rec in sorted(records, key=lambda r: (r["algo_id"], r["arr_type"])):
    algo_id = rec["algo_id"]
    algo_name = rec["algo_name"]
    arr_type = rec["arr_type"]
    df = rec["df"]

    trace_name = f"{algo_name} - {arr_type}"

    color = algo_colors.get(algo_id, "#333333")
    dash = dash_map.get(arr_type, "solid")

    fig.add_trace(go.Scatter(
        x=df["InputSize"],
        y=df["Time(us)"],
        mode="lines+markers",
        name=trace_name,
        line=dict(color=color, width=2, dash=dash),
        marker=dict(size=6, symbol="circle"),
        hovertemplate="<b>%{fullData.name}</b><br>n=%{x}<br>time=%{y} μs<extra></extra>"
    ))

fig = apply_styling(fig, "Sorting Algorithms: All Algorithms and Array Types")
fig.show()

case_map = {
    "Bubble Sort": {"best": "Sorted", "worst": "Reversed", "avg": "Random"},
    "Insertion Sort": {"best": "Sorted", "worst": "Reversed", "avg": "Random"},
    "Merge Sort": {"best": "Sorted", "worst": "Random", "avg": "Random"},
    "Heap Sort": {"best": "Sorted", "worst": "Random", "avg": "Random"},
    "Radix Sort": {"best": "Random", "worst": "Random", "avg": "Random"},
    "QuickSort (random pivot)": {"best": "Sorted", "worst": "Random", "avg": "Random"},
}

def plot_case(case: str, records):
    """
    case = "best", "worst" or "avg"
    """
    fig = go.Figure()

    for rec in sorted(records, key=lambda r: r["algo_id"]):
        algo_name = rec["algo_name"]
        arr_type_needed = case_map.get(algo_name, {}).get(case)

        if arr_type_needed and rec["arr_type"] == arr_type_needed:
            algo_id = rec["algo_id"]
            df = rec["df"]

            fig.add_trace(go.Scatter(
                x=df["InputSize"],
                y=df["Time(us)"],
                mode="lines+markers",
                name=algo_name,
                line=dict(color=algo_colors.get(algo_id, "#333333"), width=2),
                marker=dict(size=6, symbol="circle"),
                hovertemplate="<b>%{fullData.name}</b><br>n=%{x}<br>time=%{y} μs<extra></extra>"
            ))

    fig = apply_styling(fig, f"All Algorithms - {case.capitalize()} Case")
    return fig


fig_best = plot_case("best", records)
fig_worst = plot_case("worst", records)
fig_avg = plot_case("avg", records)

fig_best.show()
fig_worst.show()
fig_avg.show()
