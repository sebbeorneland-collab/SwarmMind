#!/usr/bin/env python3
"""Create an SVG chart from SwarmMind generation statistics."""

import csv
from pathlib import Path


CSV_PATH = Path("generation_stats_v2.csv")
OUTPUT_PATH = Path("generation_stats.svg")
WIDTH = 1000
HEIGHT = 600
MARGIN = 70


def points(values, minimum, maximum):
    usable_width = WIDTH - 2 * MARGIN
    usable_height = HEIGHT - 2 * MARGIN
    x_step = usable_width / max(len(values) - 1, 1)
    value_range = max(maximum - minimum, 1.0)

    return " ".join(
        f"{MARGIN + index * x_step:.1f},{HEIGHT - MARGIN - (value - minimum) / value_range * usable_height:.1f}"
        for index, value in enumerate(values)
    )


def main():
    if not CSV_PATH.exists():
        raise SystemExit(f"Could not find {CSV_PATH}")

    with CSV_PATH.open(newline="", encoding="utf-8") as file:
        rows = list(csv.DictReader(file))

    if not rows:
        raise SystemExit("The statistics file contains no generations")

    generations = [int(row["generation"]) for row in rows]
    series = {
        "Best fitness": ("#f4c542", [float(row["best_fitness"]) for row in rows]),
        "Average fitness": ("#53b7ff", [float(row["average_fitness"]) for row in rows]),
        "5-gen moving average": (
            "#72df8a",
            [float(row["moving_average_fitness_5"]) for row in rows],
        ),
    }

    all_values = [value for _, values in series.values() for value in values]
    minimum = min(all_values)
    maximum = max(all_values)

    lines = []
    legend = []
    for index, (label, (colour, values)) in enumerate(series.items()):
        lines.append(
            f'<polyline points="{points(values, minimum, maximum)}" '
            f'fill="none" stroke="{colour}" stroke-width="3" />'
        )
        legend_y = 28 + index * 24
        legend.append(
            f'<line x1="{WIDTH - 270}" y1="{legend_y}" x2="{WIDTH - 235}" '
            f'y2="{legend_y}" stroke="{colour}" stroke-width="3" />'
            f'<text x="{WIDTH - 225}" y="{legend_y + 5}" fill="#e8e8e8" '
            f'font-size="14">{label}</text>'
        )

    svg = f'''<svg xmlns="http://www.w3.org/2000/svg" width="{WIDTH}" height="{HEIGHT}">
<rect width="100%" height="100%" fill="#17191f" />
<text x="{WIDTH / 2}" y="35" text-anchor="middle" fill="#ffffff" font-size="24">SwarmMind evolution</text>
<line x1="{MARGIN}" y1="{HEIGHT - MARGIN}" x2="{WIDTH - MARGIN}" y2="{HEIGHT - MARGIN}" stroke="#888" />
<line x1="{MARGIN}" y1="{MARGIN}" x2="{MARGIN}" y2="{HEIGHT - MARGIN}" stroke="#888" />
<text x="{WIDTH / 2}" y="{HEIGHT - 20}" text-anchor="middle" fill="#cccccc">Generation {generations[0]}â€“{generations[-1]}</text>
<text x="20" y="{HEIGHT / 2}" fill="#cccccc" transform="rotate(-90 20 {HEIGHT / 2})">Fitness</text>
<text x="{MARGIN - 10}" y="{MARGIN + 5}" text-anchor="end" fill="#cccccc">{maximum:.1f}</text>
<text x="{MARGIN - 10}" y="{HEIGHT - MARGIN + 5}" text-anchor="end" fill="#cccccc">{minimum:.1f}</text>
{''.join(lines)}
{''.join(legend)}
</svg>
'''
    OUTPUT_PATH.write_text(svg, encoding="utf-8")
    print(f"Created {OUTPUT_PATH}")


if __name__ == "__main__":
    main()

