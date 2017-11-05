# graph_algo (subway path finding)

Suppose you live in (or travel to) a place called Yeiv City. One day, you decide to go to the shopping mall with your dudes, but your car is malfunctioned. You have to take the subway in order to hang out with your firends.

here is the subway map.
![alt text](https://github.com/JeffreyWang2864/graph_algo/blob/master/subway/images/subway_map.png)

However, you are so dumb that you don't know the shortest path from where you at to your destination.

In this case, my tool might be useful for you.

This repo implements a simple shortest pathfinder with Edsger W. Dijkstra's algorithm. It can easily find any shortest path if you provided the graph and data correctly.

[input graph](https://github.com/JeffreyWang2864/graph_algo/blob/master/subway/data/nodes.txt)

[dictionary](https://github.com/JeffreyWang2864/graph_algo/blob/master/subway/data/dict.txt)

---

For example, if I start at station `San Monica` and I set my destination to `Lanayru Ruins`

```c++
#define START_NAME "San Monica"
#define END_NAME "Lanayru Ruins"
```

I will get:

```
route: San Monica  -----  Lanayru Ruins

you are now at station San Monica on line 7, S. San Monica direction.
After 2 stops, at station Silver Bay transfer to line 4, E. San Monica direction.
After 2 stops, at station South Lanayru transfer to line 8, Lanayru direction.
After 1 stops, at station Lanayru transfer to line 6, De Lauret direction.
After 1 stops, at station De Lauret transfer to line 2, Lanayru Ruins direction.
after 1 stops, you arrive at your destination Lanayru Ruins.
total distance: 10310	total stops: 7
```

which clearly gives me a route
![alt text](https://github.com/JeffreyWang2864/graph_algo/blob/master/subway/images/subway_map_example.png)
