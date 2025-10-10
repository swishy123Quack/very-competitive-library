vector<Vertex*> roots;
roots.push_back(build(a, 0, n - 1)); //init
(...)
roots.push_back(update(roots.back(), 0, n - 1, x, 1)); //update at the last moment
(...)
roots.push_back(update(roots[a], 0, n - 1, x, 1)); //update at some specific moment