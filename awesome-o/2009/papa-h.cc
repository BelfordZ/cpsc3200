#include <string>
#include <map>
#include <set>
#include <iostream>
#include <sstream>
#include <cassert>

using namespace std;

enum Gender { MALE, FEMALE, UNKNOWN };

struct Person
{
  Gender gender;
  string spouse;
  string father, mother;
  set<string> children;

  Person()
    : gender(UNKNOWN)
  {
  }
};

typedef map<string, Person> Info;

ostream &operator<<(ostream &os, const Person &p)
{
  if (p.gender == MALE) {
    os << "  MALE" << endl;
  } else if (p.gender == FEMALE) {
    os << "  FEMALE" << endl;
  } else {
    os << "  UNKNOWN" << endl;
  }
  os << "  Spouse  : " << p.spouse << endl;
  os << "  Father  : " << p.father << endl;
  os << "  Mother  : " << p.mother << endl;
  os << "  Children:";
  for (set<string>::const_iterator it = p.children.begin(); 
       it != p.children.end(); ++it) {
    os << " " << *it;
  }
  os << endl;
  return os;
}

bool replace(Gender &oldg, Gender newg)
{
  assert(oldg == UNKNOWN || oldg == newg);
  bool changed = oldg != newg;
  oldg = newg;
  return changed;
}

bool replace(string &oldname, const string &newname)
{
  assert(oldname == "" || oldname == newname);
  bool changed = oldname != newname;
  oldname = newname;
  return changed;
}

bool add_spouse(Info &known, const string &wife, const string &husband)
{
  bool changed = false;
  changed |= replace(known[wife].spouse, husband);
  changed |= replace(known[wife].gender, FEMALE);
  changed |= replace(known[husband].spouse, wife);
  changed |= replace(known[husband].gender, MALE);
  return changed;
}

bool add_child(Info &known, const string &child, 
	       Gender child_g, const string &parent)
{
  bool changed = false;

  changed |= replace(known[child].gender, child_g);

  // we may not know if parent is father or mother yet
  if (known[parent].gender == MALE) {
    changed |= replace(known[child].father, parent);
  } else if (known[parent].gender == FEMALE) {
    changed |= replace(known[child].mother, parent);
  }

  if (known[parent].children.count(child) == 0) {
    known[parent].children.insert(child);
    changed = true;
  }
  return changed;
}

bool add_parent(Info &known, const string &parent, Gender parent_g, 
		const string &child)
{
  bool changed = false;

  changed |= replace(known[parent].gender, parent_g);
  if (known[parent].children.count(child) == 0) {
    known[parent].children.insert(child);
    changed = true;
  }

  if (parent_g == MALE) {
    changed |= replace(known[child].father, parent);
  } else if (parent_g == FEMALE) {
    changed |= replace(known[child].mother, parent);
  } else {
    assert(0);
  }
  return changed;
}

void process_data(Info &known, const string &line)
{
  istringstream iss(line);

  string name1, is, name2, relationship;

  iss >> name1 >> is >> name2 >> relationship;
  name2.erase(name2.length()-2, 2);   // get rid of 's 
  relationship.erase(relationship.length()-1, 1);   // get rid of .

  if (relationship == "wife") {
    add_spouse(known, name1, name2);
  } else if (relationship == "husband") {
    add_spouse(known, name2, name1);
  } else if (relationship == "daughter") {
    add_child(known, name1, FEMALE, name2);
  } else if (relationship == "son") {
    add_child(known, name1, MALE, name2);
  } else if (relationship == "mother") {
    add_parent(known, name1, FEMALE, name2);
  } else if (relationship == "father") {
    add_parent(known, name1, MALE, name2);
  } else {
    assert(0);
  }
}

string check_spouse(Info &known, const string &wife, const string &husband)
{
  if (known[wife].spouse != husband || known[husband].spouse != wife) {
    return "no";
  } else if (known[wife].gender == FEMALE && known[husband].gender == MALE) {
    return "yes";
  } else if (known[wife].gender == UNKNOWN && 
	     known[husband].gender == UNKNOWN) {
    return "unknown";
  } else {
    return "no";
  }
}

string check_child(Info &known, const string &parent, Gender parent_g,
		   const string &child, Gender child_g)
{
  if (known[parent].children.count(child) == 0) {
    return "no";
  }

  bool bad = false;
  bool unknown = false;
  
  if (parent_g != UNKNOWN) {
    if (known[parent].gender == UNKNOWN) {
      unknown = true;
    } else if (known[parent].gender != parent_g) {
      bad = true;
    }
  }

  if (child_g != UNKNOWN) {
    if (known[child].gender == UNKNOWN) {
      unknown = true;
    } else if (known[child].gender != child_g) {
      bad = true;
    }
  }

  if (bad) {
    return "no";
  } else if (unknown) {
    return "unknown";
  } else {
    return "yes";
  }
}

string check_grandchild(Info &known, const string &gparent, Gender gparent_g,
			const string &gchild, Gender gchild_g)
{
  bool unknown = false;

  for (Info::const_iterator it = known.begin(); it != known.end(); ++it) {
    const string &parent = it->first;
    string ans1 = check_child(known, gparent, gparent_g, parent, UNKNOWN);
    if (ans1 == "no") continue;
    string ans2 = check_child(known, parent, UNKNOWN, gchild, gchild_g);
    if (ans2 == "no") continue;
    if (ans1 == "yes" && ans2 == "yes") return "yes";
    unknown = true;
  }
  if (unknown) {
    return "unknown";
  } else {
    return "no";
  }
}

// currently we are not checking for nephew/niece by marriage
string check_nephew(Info &known, const string &uncle, const string &nephew,
		    Gender nephew_g)
{
  bool unknown = false;

  // it1 points to parent of uncle
  // it2 points to parent of newphew

  for (Info::const_iterator it1 = known.begin(); it1 != known.end(); ++it1) {
    if (check_child(known, it1->first, UNKNOWN, uncle, UNKNOWN) == "no") 
      continue;
    for (Info::const_iterator it2 = known.begin(); it2 != known.end(); ++it2) {
      if (check_child(known, it1->first, UNKNOWN, it2->first, UNKNOWN) == "no")
	continue;

      string ans = check_child(known, it2->first, UNKNOWN, nephew, nephew_g);
      if (ans == "no") continue;
      if (ans == "yes") return "yes";
      if (ans == "unknown") unknown = true;
    }
  }

  if (unknown) {
    return "unknown";
  } else {
    return "no";
  }
}

string process_query(Info &known, const string &line)
{
  // Note: because we assume that there are no hidden relationships, 
  // the only unknown cases are those that imply a gender but we are
  // not able to determine the gender


  istringstream iss(line);
  string name1, is, name2, relationship;
  iss >> is >> name1 >> name2 >> relationship;
  name2.erase(name2.length()-2, 2);                // get rid of 's
  relationship.erase(relationship.length()-1, 1);  // get rid of ?


  if (relationship == "wife") {
    return check_spouse(known, name1, name2);
  } else if (relationship == "husband") {
    return check_spouse(known, name2, name1);
  } else if (relationship == "daughter") {
    return check_child(known, name2, UNKNOWN, name1, FEMALE);
  } else if (relationship == "son") {
    return check_child(known, name2, UNKNOWN, name1, MALE);
  } else if (relationship == "mother") {
    return check_child(known, name1, FEMALE, name2, UNKNOWN);
  } else if (relationship == "father") {
    return check_child(known, name1, MALE, name2, UNKNOWN);
  } else if (relationship == "niece") {
    return check_nephew(known, name2, name1, FEMALE);
  } else if (relationship == "nephew") {
    return check_nephew(known, name2, name1, MALE);
  } else if (relationship == "grandfather") {
    return check_grandchild(known, name1, MALE, name2, UNKNOWN);
  } else if (relationship == "grandmother") {
    return check_grandchild(known, name1, FEMALE, name2, UNKNOWN);
  } else if (relationship == "grandson") {
    return check_grandchild(known, name2, UNKNOWN, name1, MALE);
  } else if (relationship == "granddaughter") {
    return check_grandchild(known, name2, UNKNOWN, name1, FEMALE);
  } else {
    assert(0);
  }
  return "";
}

bool propagate(Info &known, const string &name)
{
  bool changed = false;

  // marry my parents
  if (known[name].father != "" && known[name].mother != "") {
    changed |= add_spouse(known, known[name].mother, known[name].father);
  }

  // my spouses' children are mine too
  if (known[name].spouse != "") {
    set<string> &child = known[known[name].spouse].children;
    for (set<string>::const_iterator it = child.begin(); it != child.end();
	 ++it) {
      changed |= known[name].children.insert(*it).second;
    }
  }

  // if I share a child with someone else, then we are married
  //
  // this is needed if I have an unknown gender, because the child would
  // not link to me as a father or mother.
  for (Info::iterator it = known.begin(); it != known.end(); ++it) {
    if (it->first == name) continue;
    set<string> &child = known[name].children;
    for (set<string>::const_iterator it2 = child.begin(); it2 != child.end();
	 ++it2) {
      if (it->second.children.count(*it2) > 0) {
	changed |= replace(known[name].spouse, it->first);
	changed |= replace(it->second.spouse, name);
	break;
      }
    }
  }

  // if I know my gender then my children know whether I am father or mother
  if (known[name].gender != UNKNOWN) {
    for (set<string>::const_iterator it = known[name].children.begin();
	 it != known[name].children.end(); ++it) {
      changed |= add_parent(known, name, known[name].gender, *it);
    }
  }

  // if I know my gender then my spouse's gender is known too
  if (known[name].gender != UNKNOWN && known[name].spouse != "") {
    string &spouse = known[name].spouse;
    changed |= replace(known[spouse].gender,
		       (known[name].gender == MALE) ? FEMALE : MALE);
  }

  return changed;
}

void propagate(Info &known)
{
  bool changed = true;

  while (changed) {
    changed = false;
    for (Info::iterator it = known.begin(); it != known.end(); ++it) {
      changed |= propagate(known, it->first);
    }
  }
}

void check_consistency(const Info &known)
{
  for (Info::const_iterator it = known.begin(); it != known.end(); ++it) {
    const string &name = it->first;
    const Person &person = it->second;

    // make sure that a person is not the spouse, parent, or child of self
    if (name == person.spouse || person.children.count(name) > 0 ||
	name == person.father || name == person.mother) {
      cerr << name << " has inconsistent information" << endl;
    }

    // make sure that if I have a spouse then the spouse has me too
    if (person.spouse != "" && known.at(person.spouse).spouse != name) {
      cerr << name << " and " << person.spouse 
	   << " have inconsistent spousal information" << endl;
    }

    // make sure that if I have a father or mother then they have me
    // as a child too
    if (person.father != "" && 
	known.at(person.father).children.count(name) == 0) {
      cerr << name << " and " << person.father 
	   << " have incosistent parent-child information" << endl;
    }

    if (person.mother != "" && 
	known.at(person.mother).children.count(name) == 0) {
      cerr << name << " and " << person.mother 
	   << " have incosistent parent-child information" << endl;
    }
  }
  

}

int main(void)
{
  string line;
  Info known;

  while (getline(cin, line) && line != "") {
    process_data(known, line);
  }
  
  propagate(known);
  check_consistency(known);

#ifdef DEBUG
  for (Info::iterator it = known.begin(); it != known.end(); ++it) {
    cout << it->first << ":" << endl;
    cout << it->second;
    cout << "=================" << endl;
  }
#endif

  while (getline(cin, line)) {
    cout << process_query(known, line) << endl;
  }

  return 0;
}
