import folium
import webbrowser
import os

from numpy import double

points = []
with open('points.txt') as f:
   for line in f:
       try:
            p = double(line)
            degrees = p / 100
            minutes = p - (degrees * 100)
            seconds=minutes/60
            r = degrees+seconds
            points.append(r)

       except:
            break

       if 'str' in line:
          break

center = [30.0444, 31.2357]
map = folium.Map(location=center, zoom_start=14)

for i in range(len(points)):
    if i < (len(points) - 1):
        folium.CircleMarker(location=[points[i], points[i+1]], radius=0.5, color='black').add_to(map)
        if i >= 2:
            folium.PolyLine([[points[i-2], points[i-1]], [points[i], points[i+1]]], color='black').add_to(map)

map.save('map.html')

filename = 'file:///'+os.getcwd()+'/' + 'map.html'
webbrowser.open_new_tab(filename)