ordset<int> s;
s.insert(1);
s.insert(2);
s.insert(4);
s.find_by_order(0) //Returns 1
s.order_of_key(4) //Returns 2 