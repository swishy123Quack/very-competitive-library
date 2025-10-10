Graph G(n);
for (int i = 0; i < m; i++){
    int u, v; cin >> u >> v;
    G.add(--u, --v);
}

StronglyConnected scc(G);