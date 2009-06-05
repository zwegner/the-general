// Roles are a bunch of constants

// Constants are all inside enums denoting their type, but they might as well
// be in one enum since every single one has a different value. This is so that
// anything that is syntactically distinct is also numerically distinct

// roles
enum ROLES { role_a_ = START_ROLES };

// actions
enum ACTION_1 { action_1_a_ = START_ACTION_1, action_1_b_, action_1_c_ };
struct ACTION
{
	BOOL is_noop_;
	enum ACTION_1 action_1_;
}

struct STATE
{
	// stuff
};

void init(struct STATE *state)
{
	// set state to initial
}

// Get a list of actions which the given role can take in the current state.
// Returns the number of actions available.
int get_legal_actions(struct STATE *state, enum ROLE role,
	struct ACTION *a_list)
{
}

BOOL is_terminal(struct STATE *state)
{
}

int goal(struct STATE *state, enum ROLE role)
{
}
