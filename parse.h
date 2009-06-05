enum relation_type { relation_true, relation_init, relation_role, relation_does,
  relation_next, relation_legal, relation_goal, relation_terminal,
  relation_distinct, relation_x };

struct relation_t {
  enum relation_type type;

};

enum relation read_relation();
