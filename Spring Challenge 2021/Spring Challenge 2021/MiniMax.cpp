#include "MiniMax.h"

#include "Utility.h"
#include "Florest.h"

auto delete_nodes = delete_all<std::list<ActionNode*>>;

bool operator==(ActionNode const& rhs, ActionNode const& lhs)
{
	return (rhs.m_sun_income == lhs.m_sun_income && rhs.m_sun_income == lhs.m_sun_points) ? true : false;
}

bool operator>(ActionNode const& rhs, ActionNode const& lhs)
{
	return (rhs.m_sun_income > lhs.m_sun_income 
		|| (rhs.m_sun_income == lhs.m_sun_income && rhs.m_sun_points > lhs.m_sun_points) 
		|| (rhs.m_sun_income == lhs.m_sun_income && rhs.m_sun_points == lhs.m_sun_points 
			&& rhs.m_action > lhs.m_action)) ? true : false;
}

bool operator<(ActionNode const& rhs, ActionNode const& lhs)
{
	return (rhs > lhs || rhs == lhs) ? false : true;
}

bool operator>=(ActionNode const& rhs, ActionNode const& lhs)
{
	return (rhs < lhs) ? false : true;
}

bool operator<=(ActionNode const& rhs, ActionNode const& lhs)
{
	return (rhs > lhs) ? false : true;
}

std::ostream& operator<<(std::ostream& os, ActionNode const& node)
{
	os << "Node" << std::endl;
	os << "Action: " << ActionNode::get_action_string(node.m_action) << std::endl;
	os << "Income: " << node.m_sun_income << std::endl;
	os << "Sun Points: " << node.m_sun_points << std::endl;

	return os;
}

ActionNode::ActionNode(int sun_income, int sun_points, int seeds_count, int stree_count, int mtree_count, int ltree_count,
	int seeds_available_count, int stree_available_count, int mtree_available_count, int ltree_available_count)
: m_action(ACT_WAIT)
, m_sun_income(sun_income)
, m_sun_points(sun_points)
, m_seeds_count(seeds_count)
, m_stree_count(stree_count)
, m_mtree_count(mtree_count)
, m_ltree_count(ltree_count)
, m_seeds_available_count(seeds_available_count)
, m_stree_available_count(stree_available_count)
, m_mtree_available_count(mtree_available_count)
, m_ltree_available_count(ltree_available_count)
, m_parent(nullptr)
{
}

ActionNode::ActionNode(ActionNode const* const parent, Action action)
	: m_action(action)
	, m_sun_income(parent->m_sun_income)
	, m_sun_points(parent->m_sun_points)
	, m_seeds_count(parent->m_seeds_count)
	, m_stree_count(parent->m_stree_count)
	, m_mtree_count(parent->m_mtree_count)
	, m_ltree_count(parent->m_ltree_count)
	, m_seeds_available_count(parent->m_seeds_available_count)
	, m_stree_available_count(parent->m_stree_available_count)
	, m_mtree_available_count(parent->m_mtree_available_count)
	, m_ltree_available_count(parent->m_ltree_available_count)
	, m_parent(parent)
{
	switch (action)
	{
	case ACT_SEED_SMALL:
		m_sun_points -= m_seeds_count;
		m_stree_available_count--;
		m_seeds_count++;
		break;
	case ACT_SEED_MEDIUM:
		m_sun_points -= m_seeds_count;
		m_mtree_available_count--;
		m_seeds_count++;
		break;
	case ACT_SEED_LARGE:
		m_sun_points -= m_seeds_count;
		m_ltree_available_count--;
		m_seeds_count++;
		break;
	case ACT_GROWTOSMALL:
		m_sun_points -= 1 + m_stree_count;
		m_seeds_count--;
		m_seeds_available_count--;
		m_stree_count++;
		m_sun_income++;
		break;
	case ACT_GROWTOMEDIUM:
		m_sun_points -= 3 + m_mtree_count;
		m_stree_count--;
		m_stree_available_count--;
		m_mtree_count++;
		m_sun_income++;
		break;
	case ACT_GROWTOLARGE:
		m_sun_points -= 7 + m_ltree_count;
		m_mtree_count--;
		m_mtree_available_count--;
		m_ltree_count++;
		m_sun_income++;
		break;
	case ACT_COMPLETE:
		m_sun_points -= 4;
		m_ltree_count--;
		m_ltree_available_count--;
		m_sun_income--;
		break;
	case ACT_WAIT:
		m_sun_points += m_sun_income;
		m_seeds_available_count = m_seeds_count;
		m_stree_available_count = m_stree_count;
		m_mtree_available_count = m_mtree_count;
		m_ltree_available_count = m_ltree_count;
		break;

	default:
		std::cerr << "This action doesn't exist." << std::endl;
		exit(EXIT_FAILURE);
		break;
	}
}

ActionNode::ActionNode(ActionNode&& other)
: m_action(other.m_action)
, m_sun_income(other.m_sun_income)
, m_sun_points(other.m_sun_points)
, m_seeds_count(other.m_seeds_count)
, m_stree_count(other.m_stree_count)
, m_mtree_count(other.m_mtree_count)
, m_ltree_count(other.m_ltree_count)
, m_seeds_available_count(other.m_seeds_available_count)
, m_stree_available_count(other.m_stree_available_count)
, m_mtree_available_count(other.m_mtree_available_count)
, m_ltree_available_count(other.m_ltree_available_count)
, m_parent(other.m_parent)
, m_childs(std::move(other.m_childs))
{

}

ActionNode::~ActionNode()
{
	delete_nodes(m_childs);
}

std::string ActionNode::get_action_string(Action action)
{
	std::string action_str;
	switch (action)
	{
	case ACT_SEED_SMALL:
		action_str = "stree - seed";
		break;
	case ACT_SEED_MEDIUM:
		action_str = "mtree - seed";
		break;
	case ACT_SEED_LARGE:
		action_str = "ltree - seed";
		break;
	case ACT_GROWTOSMALL:
		action_str = "grows";
		break;
	case ACT_GROWTOMEDIUM:
		action_str = "growm";
		break;
	case ACT_GROWTOLARGE:
		action_str = "growl";
		break;
	case ACT_COMPLETE:
		action_str = "complete";
		break;
	case ACT_WAIT:
		action_str = "wait";
		break;
	default:
		std::cerr << "This action doesn't exist." << std::endl;
		exit(EXIT_FAILURE);
		break;
	}
	return action_str;
}

void ActionNode::print_tree()
{
	std::cerr << "Node depth:" << get_depth() << std::endl;
	std::string tree_string;
	int number_of_lines = 0;
	print_tree_helper(tree_string, "", *this, true, number_of_lines);
	std::cerr << tree_string << std::endl;
}

void ActionNode::print_tree_helper(std::string& tree_string, std::string prefix, ActionNode const& node, bool is_last, int& numer_of_lines)
{
	constexpr int max_lines = 50;
	if (numer_of_lines > 50)
	{
		return;
	}
	numer_of_lines++;

	tree_string += prefix;
	
	tree_string += (is_last ? "|___" : "|---");

	tree_string += get_action_string(node.m_action) + " " + std::to_string(node.m_sun_income) + " " + std::to_string(node.m_sun_points) + "\n";

	int i = 0;
	for (auto begin = node.m_childs.begin(), end = node.m_childs.end(); begin != end; ++begin)
	{
		auto aux_it = begin;
		print_tree_helper(tree_string, prefix + (is_last ? "    " : "|   "), *(*begin), (++aux_it == end), numer_of_lines);
	}
}

int ActionNode::get_depth()
{
	int depth = 0;
	for (auto aux_node : m_childs)
	{
		int aux_depth = 0;
		aux_depth = aux_node->get_depth();
		aux_depth++;
		if (aux_depth > depth)
			depth = aux_depth;
	}
	return depth;
}

bool ActionNode::is_valid()
{
	return (m_sun_income >= 0
		&& m_sun_points >= 0
		&& m_seeds_available_count >= 0
		&& m_seeds_count <= 2							// Todo: get a better rule here.
		&& m_stree_available_count >= 0
		&& m_mtree_available_count >= 0
		&& m_ltree_available_count >= 0) ? true : false;
}

MiniMax::MiniMax(int sun_income, int sun_points, int seeds_count, int stree_count, int mtree_count, int ltree_count,
	int seeds_available_count, int stree_available_count, int mtree_available_count, int ltree_available_count)
:m_root(new ActionNode(sun_income, sun_points, seeds_count, stree_count, mtree_count, ltree_count,
	seeds_available_count, stree_available_count, mtree_available_count, ltree_available_count))
{
}

MiniMax::~MiniMax()
{
	delete m_root;
}

Action MiniMax::early_choose_seed(ActionNode* node)
{
	//if (node == nullptr)
	//{
	//	std::cerr << "Node doesnt exit" << std::endl;
	//	exit(EXIT_FAILURE);
	//}

	if (node->m_ltree_available_count)
		return ACT_SEED_LARGE;
	else if (node->m_mtree_available_count)
		return ACT_SEED_MEDIUM;
	else
		return ACT_SEED_SMALL;
}

void MiniMax::generate_childs(ActionNode* node, std::vector<Action>const& possible_actions, int depth)
{
	constexpr int SEEDS_ACTION = (ACT_SEED_SMALL | ACT_SEED_MEDIUM | ACT_SEED_LARGE);

	if (depth == 1)
		return;

	for (auto it = possible_actions.begin(), end = possible_actions.end(); it != end; ++it)
	{
		ActionNode* child;
		
		if (*it == ACT_SEED_SMALL)
		{
			child = new ActionNode(node, early_choose_seed(node));
			it += 2;
		}
		else
		{
			child = new ActionNode(node, *it);
		}
		
		if (!child->is_valid())		// Delete if its not a valid action
		{
			delete child;
			continue;
		}
		else
		{
			number_of_nodes++;
		
			//if (number_of_nodes > 2000 * debug_helper)
			//{
			//	std::cerr << "depth: " << m_root.get_depth() << std::endl;
			//	debug_helper++;
			//}
			//std::cerr << "depth " << depth << std::endl;
			//std::cerr << child << std::endl;
			if (*it == ACT_WAIT)
				generate_childs(child, possible_actions, depth + 1);
			else
				generate_childs(child, possible_actions, depth);
			node->m_childs.push_back(child);
		}
	}
}

void MiniMax::construct_tree()
{
	std::vector<Action>vec_possible_actions;
	if (Florest::get_instance()->get_day() < 17)
	{
		vec_possible_actions.insert(vec_possible_actions.end(), 
			{ ACT_WAIT
			, ACT_SEED_SMALL
			, ACT_SEED_MEDIUM
			, ACT_SEED_LARGE
			, ACT_GROWTOSMALL
			, ACT_GROWTOMEDIUM
			, ACT_GROWTOLARGE});
	}
	else
	{
		vec_possible_actions.insert(vec_possible_actions.end(),
			{ ACT_WAIT
			, ACT_GROWTOSMALL
			, ACT_GROWTOMEDIUM
			, ACT_GROWTOLARGE
			, ACT_COMPLETE });
	}
	generate_childs(m_root, vec_possible_actions, 0);
	std::cerr << "Number of nodes: " << number_of_nodes << std::endl;
	//m_root->print_tree();														
}

ActionNode* MiniMax::get_best_child(ActionNode* node)
{
	ActionNode* best_child = nullptr;

	for (auto aux_node : node->m_childs)
	{
		{
			ActionNode* aux_best_child = get_best_child(aux_node);
			if (aux_best_child != nullptr)
			{
				aux_node->m_sun_points = aux_best_child->m_sun_points;
				aux_node->m_sun_income = aux_best_child->m_sun_income;
			}
		}

		if (best_child == nullptr)
			best_child = aux_node;
		else
		{
			if (*aux_node > *best_child)
				best_child = aux_node;
		}
	}
	return best_child;
}

Action MiniMax::choose_action()
{																// Debug
	ActionNode* best_child = get_best_child(m_root);
	//std::cerr << ActionNode::get_action_string(best_child->m_action) << std::endl;			// Debug
	return best_child->m_action;
}
