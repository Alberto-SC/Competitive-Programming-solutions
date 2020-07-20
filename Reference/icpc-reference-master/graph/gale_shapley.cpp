Assign each person to be free;
  	while (some man m is free) do
  	begin
  		w := first woman on ms list;
  		m proposes, and becomes engaged, to w;
  		if (some man m' is engaged to w) then
  		    assign m' to be free;
  		for each (successor m'' of m on ws list) do
  			delete the pair (m'', w)
 	  end;
   	output the engaged pairs, which form a stable matching
