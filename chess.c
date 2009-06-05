#define ANY -1

// Roles are a bunch of constants

// Constants are all inside enums denoting their type, but they might as well
// be in one enum since every single one has a different value. This is so that
// anything that is syntactically distinct is also numerically distinct

////////////////////////////////////////////////////////////////////////////////
// Roles ///////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
enum ROLE { role_white = START_ROLES, role_black };

////////////////////////////////////////////////////////////////////////////////
// Actions /////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
enum ACTION_TYPE { action_move = START_ACTIONS, action_noop };

struct move
{
	// P e 2 e 4
	int arg_1; // piece
	int arg_2; // from file
	int arg_3; // from rank
	int arg_4; // to file
	int arg_5; // to rank
};

struct ACTION
{
	int type;
	union
	{
		struct move move;
		// noop --> singleton, no data stored
		// theoretically, other moves--resign, etc.
	};
};


////////////////////////////////////////////////////////////////////////////////
// Facts ///////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
enum FACT_TYPE { fact_cell = START_FACTS, fact_check };
// game specific stuff
struct fact_cell
{
	// N @ f 3
	int arg_1; // f
	int arg_2; // 3
	int arg_3; // N
};

struct STATE
{
	struct fact_cell *fl_cell;
	struct fact_step *fl_step;
	struct fact_check *fl_check;
	int fl_cell_len;
	int fl_step_len;
	int fl_check_len;
	// step 1
	// cell A 1 WR
	// cell C 3 B
	// control WHITE
	// etc.
};

void init(struct STATE *state)
{
	struct fact_cell f1[1];
	// set state to initial
	f1->arg_1 = sym_a;
	f1->arg_2 = sym_1;
	f1->arg_3 = sym_wr;
	add_fact_cell(state, f1);

}

// Get a list of actions which the given role can take in the current state.
// Returns the number of actions available.
int get_legal_actions(struct STATE *state, enum ROLE role,
	struct ACTION *a_list)
{
}

// Returns whether the
BOOL is_terminal(struct STATE *state)
{
}

// Returns the goal value for "role" in the current state. Should only be called
// if state is also terminal.
int goal(struct STATE *state, enum ROLE role)
{
}

// Set next_state to be the state of the game after each role performs their
// action to state.
void set_next_state(struct STATE next_state, struct STATE *state,
		struct ACTION *actions)
{
	if (state.move)

	if (state.control == control_white)
		next_state.control = control_black;
	if (state.control == control_black)
		next_state.control = control_white;
}

int rel_succ_1(int arg_1)
{
	switch(arg_1)
	{
		case sym_1: return sym_2;
		case sym_2: return sym_3;
		case sym_3: return sym_4;
		// etc
	}
}
int rel_succ_2(int arg_2)
{
	switch(arg_2)
	{
		case sym_2: return sym_1;
		case sym_3: return sym_2;
		case sym_4: return sym_3;
		// etc
	}
}
// optimize as lookup table?
BOOL rel_coordinate(int arg)
{
	switch(arg)
	{
		case ...: return FALSE;
		case sym_1: return TRUE;
		case sym_1: return TRUE;
		case sym_1: return TRUE;
		case ...: return FALSE;
	}
}
