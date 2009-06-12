void init()
{
	state.add_cell(1,1,b);
	state.add_cell(1,2,b);
	state.add_cell(1,3,b);
	state.add_cell(2,1,b);
	//...
	state.add_control(x);
}

void next()
{
	// add mark
	for each player {
		if (move[player] = mark)
			next.add_cell(mark.x, mark.y, player);
	}
	// keep mark
	for each player {
		if (move[player] = mark) { // test = number of roles
			for each x { for each y { for each c {
				if state.has_cell(x,y,c) && distinct_cell(x,y,mark.x,mark.y)
					next.add_cell(x,y,c);
			}}}
		}
	}
	// control
	if (state.control(x))
		next.set_control(o);
	if (state.control(o))
		next.set_control(x);
}

bool row(x,player)
{
	if (has_cell(x,1,player) && has_cell(x,2,player) && has_cell(x,3,player))
		return true;
	return false;
}
bool column(y,player)
{
	if (has_cell(1,y,player) && has_cell(2,y,player) && has_cell(3,y,player))
		return true;
	return false;
}
bool diagonal(player)
{
	if (has_cell(1,1,player) && has_cell(2,2,player) && has_cell(3,3,player))
		return true;
	if (has_cell(1,3,player) && has_cell(2,2,player) && has_cell(3,1,player))
		return true;
	return false;
}
bool line(player)
{
	if (diagonal(player))
		return true;
	for each column {
		if (column(c,player))
			return true;
	}
	for each row {
		if (row(r,player))
			return true;
	}
	return false;
}
bool open()
{
	for each row { for each column {
		if (has_cell(r,c,b))
			return true;
	}
	return false;
}
bool distinct_cell(x,y,r,c)
{
	if (x!=r)
		return true;
	if (y!=c)
		return true;
	return false;
}
