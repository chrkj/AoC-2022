#include "Day13.h"

#define INPUT "Day13/1.IN"

struct Value : public variant<int, vector<Value>>
{
	Value() : variant(0) {}
	Value(int v) : variant(v) {}
	Value(const vector<Value>& v) : variant(v) {}
	bool operator < (const Value& rhs) const;
};

struct CompareVisitor
{
	bool operator ()(int l, int r) const
	{
		return l < r;
	}
	bool operator ()(const vector<Value>& l, const vector<Value>& r) const
	{
		return lexicographical_compare(l.begin(), l.end(), r.begin(), r.end());
	}
	bool operator ()(int l, const vector<Value>& r) const
	{
		return operator()(vector<Value>{l}, r);
	}
	bool operator ()(const vector<Value>& l, int r) const
	{
		return operator()(l, vector<Value>{r});
	}
} compareVisitor;

bool Value::operator < (const Value& rhs) const
{
	return visit(compareVisitor, *this, rhs);
}

Value parse(std::string_view& s)
{
	if (s[0] == '[')
	{
		vector<Value> vr;
		if (s[1] != ']')
		{
			while (s[0] != ']')
			{
				s.remove_prefix(1);
				vr.push_back(parse(s));
			}
			s.remove_prefix(1);
		}
		else
			s.remove_prefix(2);
		return vr;
	}
	else
	{
		int v;
		auto p = from_chars(s.data(), s.data() + s.size(), v);
		s.remove_prefix(p.ptr - s.data());
		return v;
	}
}

Value parse(const std::string& s)
{
	string_view sv = s;
	return parse(sv);
}

void Day13::Part1()
{
    ScopedTimer timer;

	auto input = Utils::ReadInput(INPUT);
	
	int runningSum = 0;
	vector<Value> all;
	for (size_t i = 0; i < input.size(); i++)
	{
		if (input[i].size() == 0) 
			continue;

		Value v = parse(input[i]);
		all.push_back(v);
		if (all.size() % 2 == 0 && all[all.size() - 2] < all.back())
			runningSum += (all.size() / 2);
	}
	printf("Sum: %d", runningSum);
}

void Day13::Part2()
{
	ScopedTimer timer;

	auto input = Utils::ReadInput(INPUT);

	vector<Value> all;
	for (size_t i = 0; i < input.size(); i++)
	{
		if (input[i].size() == 0)
			continue;

		Value v = parse(input[i]);
		all.push_back(v);
	}

	Value v2 = parse("[[2]]"s), v6 = parse("[[6]]"s);
	all.push_back(v2);
	all.push_back(v6);
	sort(all.begin(), all.end());
	size_t p2 = lower_bound(all.begin(), all.end(), v2) - all.begin();
	size_t p6 = lower_bound(all.begin(), all.end(), v6) - all.begin();
	printf("Decoder key: %u", (p2 + 1) * (p6 + 1));
}
