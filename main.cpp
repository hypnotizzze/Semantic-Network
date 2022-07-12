#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <set>

using namespace std;

enum type_link
{
	None, //0
	Gen, //1
	Sit, //2
	Neg, //3
	Ins, //4
	Com, //5
	Cor, //6
	Fin, //7
	Caus, //8
	Pot //9
};

typedef struct {
	int type;
	int vertex1, vertex2;
} for_search;

bool operator== (const for_search& a, const for_search& b) {
	return ((a.type == b.type) && (a.vertex1 == b.vertex1) && (a.vertex2 == b.vertex2));
}

typedef struct {
	string name_of_link, _to;
	int type_link; // тип связи
} Link;

bool operator== (const Link &a, const Link &b) {
	return ((a.name_of_link == b.name_of_link) && (a.type_link == b.type_link) && (a._to == b._to));
}

typedef struct {
	set <string> nodes;
	map <string, vector<Link>> nodes_with_links;
} Sem_set;

void add_node(Sem_set *s) {
	int count;
	string name_of_node;
	set<string>::iterator it;
	cout << "Введите имя добавляемой вершины: ";
	cin.get();
	getline(cin, name_of_node);
	count = s->nodes.count(name_of_node);
	if (count > 0) {
		cout << "Данная вершина уже добавлена в семантическую сеть\n\n";
	}
	else {
		s->nodes.emplace(name_of_node);
		it = s->nodes.find(name_of_node);
		cout << "Вершина: " << *it << " добавлена в сеть\n\n";
	}
}

void delete_node(Sem_set *s) {
	int count;
	string name_of_node;
	cin.get();
	cout << "Введите имя удаляемой вершины: ";
	getline(cin, name_of_node);
	count = s->nodes.count(name_of_node);
	if (count == 0) {
		cout << "Данная вершина не найдена в семантической сети\n\n";
	}
	else if (count == 1) {
		s->nodes.erase(name_of_node);
		if (s->nodes_with_links.count(name_of_node) == 1) {
			s->nodes_with_links.erase(name_of_node);
		}
		cout << "Вершина: " << name_of_node << " удалена из сети\n\n";
	}
}

void edit_node(Sem_set* s) {
	int count;
	string name_of_node, name_2;
	cout << "Введите имя вершины для редактирования: ";
	cin.get();
	getline(cin, name_of_node);
	count = s->nodes.count(name_of_node);
	if (count == 0) {
		cout << "Данная вершина не найдена в семантической сети\n\n";
	}
	else if (count == 1) {
		do {
			cout << "Введите новое имя вершины: ";
			getline(cin, name_2);
			count = s->nodes.count(name_2);
			if (count == 1) {
				cout << "Вершина" << name_2 << " уже присутствует в сети, повторите ввод\n";
			}
		} while (count == 1);
		auto tmp = s->nodes.find(name_of_node);
		if (tmp != end(s->nodes))
		{
			s->nodes.erase(tmp);
			s->nodes.emplace(name_2);
		}
		auto tmp_2 = s->nodes_with_links.find(name_of_node);
		if (tmp_2 != end(s->nodes_with_links))
		{
			auto const value = move(tmp_2->second);
			s->nodes_with_links.erase(tmp_2);
			s->nodes_with_links.emplace(name_2, value);
		}
		cout << "Вершина: " << name_of_node << " изменена на " << name_2 << "\n\n";
	}
}

void enter_link_data(string &str, int &type) {
	bool end = false;
	cout << "Введите имя связи: ";
	getline(cin, str);
	do {
		cout << "Типы связей:\n";
		cout << "1) Gen - генеративная,  Sit - ситуативная, Neg - негативная\n";
		cout << "2) Ins - инструментальная\n";
		cout << "3) Com - коммитативная,  Cor - коррелятивная\n";
		cout << "4) Fin - финитивная,  Caus - каузальная, Pot - потенсивная\n";
		cout << "Введите тип связи (Gen - 1, Sit - 2, Neg - 3, Ins - 4, Com - 5, Cor - 6, Fin - 7, Caus - 8, Pot - 9: ";
		cin >> type;
		cout << "\n";
		if (type > 0 && type < 10) {
			end = true;
		}
		else
			cout << "Введен неверный тип связи\n";
	} while (end == false);
}

string show_name_link(int link) {
	string type;
	link = abs(link);
	switch (link) {
	case 1:
		type = "Gen";
		break;

	case 2:
		type = "Sit";
		break;

	case 3:
		type = "Neg";
		break;

	case 4:
		type = "Ins";
		break;

	case 5:
		type = "Ins";
		break;

	case 6:
		type = "Cor";
		break;

	case 7:
		type = "Fin";
		break;

	case 8:
		type = "Caus";
		break;

	case 9:
		type = "Pot";
		break;
	}
	return type;
}

bool check_add(Sem_set s, string ver1, string ver2, int type_link) {
	bool finded = false;
	Link link;
	auto it = s.nodes.find(ver1);
	for (auto i1 = s.nodes_with_links[*it].begin(); i1 != s.nodes_with_links[*it].end() && finded == false; ++i1) {
		link = *i1;
		if (link.type_link == type_link && link._to == ver2 && link.type_link > 0) {
			finded = true;
		}
	}
	if (type_link == Sit || type_link == Com || type_link == Caus) {
		it = s.nodes.find(ver2);
		for (auto i1 = s.nodes_with_links[*it].begin(); i1 != s.nodes_with_links[*it].end() && finded == false; ++i1) {
			link = *i1;
			if (link.type_link == type_link && link._to == ver1 && link.type_link > 0) {
				finded = true;
			}
		}
	}
	return finded;
}

void add_link(Sem_set *s) {
	int count, type;
	string name_1, name_2, name_3;
	bool end = false, link_flag = false;
	cin.get();
	if (s->nodes.size() >= 2) {
		do {
			cout << "Введите имя вершины 1: ";
			getline(cin, name_1);
			count = s->nodes.count(name_1);
			if (count == 0) {
				cout << "Данная вершина не найдена в семантической сети, повторите попытку\n";
			}
		} while (count == 0);
		do {
			cout << "Введите имя вершины 2: ";
			getline(cin, name_2);
			count = s->nodes.count(name_2);
			if (count == 0) {
				cout << "Данная вершина не найдена в семантической сети, повторите попытку\n";
			}
		} while (count == 0);
		
		do {
			enter_link_data(name_3, type);
			link_flag = check_add(*s, name_1, name_2, type);
			if (link_flag == true)
				cout << "Связь типа " << show_name_link(type) << " невозможно добавить, повторите попытку\n\n";
		} while (link_flag == true);

		cin.get();
		Link link;
		link.name_of_link = name_3;
		link._to = name_2;
		link.type_link = type;
		s->nodes_with_links.emplace(piecewise_construct, make_tuple(name_1), make_tuple()); // добавление связи +
		s->nodes_with_links[name_1].push_back(link);

		s->nodes_with_links.emplace(piecewise_construct, make_tuple(name_2), make_tuple()); // нужна ли связь с отр. значением?
		if(link.type_link != Neg && link.type_link != Cor)
			link.type_link = -type;
		link._to = name_1;
		s->nodes_with_links[name_2].push_back(link);

	}
	else {
		cout << "Недостаточно элементов, чтобы добавить связь\n\n";
	}
}

void delete_link(Sem_set *s) {
	int count, i = 0;
	string name_1, name_2, name_node, name_link;
	bool find_link = false;
	Link link, link_mem;
	if (s->nodes_with_links.size() > 0) {
		do {
			cout << "Введите у какой вершины удалить связь: ";
			cin >> name_1;
			count = s->nodes_with_links.count(name_1);
			if (count == 0)
				cout << "Вершина с таким именем не найдена, пвоторите ввод\n";
		} while (count == 0);
		auto it = s->nodes.find(name_1);
		cin.get();
		do {
			cout << "Введите имя связи для удаления: ";
			cin >> name_2;
			for (auto iter = s->nodes_with_links[*it].begin(); iter != s->nodes_with_links[*it].end(); ++iter) {
				link = *iter;
				if (link.name_of_link == name_2 && link.type_link > 0) {
					name_link = show_name_link(link.type_link);
					cout << i + 1 << ") " << *it << " " << link.name_of_link << " (" << name_link << ") " << link._to << "\n";
					i++;
					find_link = true;
				}
			}
			cout << "\n";
			cin.get();
			auto edit = s->nodes_with_links[*it].begin();
			if (find_link == false)
				cout << "Связь не найдена, повторите попытку\n";
			else { 
				if (i > 1) { // больше одной связи
					do {
						cout << "Введите номер связи для удаления: ";
						cin >> count;
						if (count <= 0 || count > i)
							cout << "Введено неверное значение, повторите попытку\n";
					} while (count <= 0 || count > i);
				}
				i = 1;
				for (auto iter = s->nodes_with_links[*it].begin(); iter != s->nodes_with_links[*it].end(); ++iter) {
					link = *iter;
					if (link.name_of_link == name_2 && count == i && link.type_link > 0) {
						edit = iter;
						link_mem.name_of_link = link.name_of_link;
						if(link.type_link != Neg && link.type_link != Cor)
							link_mem.type_link = -link.type_link;
						else
							link_mem.type_link = link.type_link;
						link_mem._to = *it;
						name_node = link._to;
						i++;
					}
				}
				s->nodes_with_links[*it].erase(edit); // link +++
				if (s->nodes_with_links[*it].size() == 0)
					s->nodes_with_links.erase(*it);

				for (auto iter = s->nodes_with_links[name_node].begin(); iter != s->nodes_with_links[name_node].end(); ++iter) { // link ---
					link = *iter;
					if (link == link_mem) {
						edit = iter;
					}
				}
				s->nodes_with_links[name_node].erase(edit);
				if (s->nodes_with_links[name_node].size() == 0)
					s->nodes_with_links.erase(name_node);
			}
		} while (find_link == false);
	}
	else
		cout << "В сети нет связей\n\n";
}

void edit_link(Sem_set *s) {
	int count, i = 0;
	string name_1, name_2, name_link;
	bool find_link = false, end;
	Link link, link_for1, link_for2, link_mem;
	if (s->nodes_with_links.size() > 0) {
		do {
			cout << "Введите у какой вершины изменить связь: ";
			cin >> name_1;
			count = s->nodes_with_links.count(name_1);
			if (count == 0)
				cout << "Вершина с таким именем не найдена, пвоторите ввод\n";
		} while (count == 0);
		auto it = s->nodes.find(name_1);
		cin.get();
		do {
			cout << "Введите имя связи для изменения: ";
			cin >> name_2;
			for (auto iter = s->nodes_with_links[*it].begin(); iter != s->nodes_with_links[*it].end(); ++iter) {
				link = *iter;
				if (link.name_of_link == name_2 && link.type_link > 0) {
					name_link = show_name_link(link.type_link);
					cout << i + 1 << ") " << *it << " " << link.name_of_link << " (" << name_link << ") " << link._to << "\n";
					i++;
					find_link = true;
				}
			}
			cout << "\n";
			cin.get();
			auto edit = s->nodes_with_links[*it].begin();
			if (find_link == false)
				cout << "Связь не найдена, повторите попытку\n";
			else if (i > 1) { // больше одной связи
				do {
					cout << "Введите номер связи для изменения: ";
					cin >> count;
					if (count <= 0 || count > i)
						cout << "Введено неверное значение, повторите попытку\n";
				} while (count <= 0 || count > i);

				// ввод новых значений связи
				cin.get();
				enter_link_data(link_for1.name_of_link, link_for1.type_link);
				link_for2.name_of_link = link_for1.name_of_link;
				link_for2.type_link = -link_for1.type_link;
				link_for2._to = name_1;

				i = 0;
				for (auto iter = s->nodes_with_links[*it].begin(); iter != s->nodes_with_links[*it].end(); ++iter) {
					link = *iter;
					if (link.name_of_link == name_2 && link.type_link > 0) {
						i++;
						if (count == i) {
							edit = iter;
							link_for1._to = link._to;
							link_mem.name_of_link = link.name_of_link;
							if(link_mem.type_link != Neg && link_mem.type_link != Cor)
							  link_mem.type_link = -link.type_link;
							link_mem._to = *it;
						}
					}
				}
				s->nodes_with_links[*it].erase(edit); // link +++
				s->nodes_with_links.emplace(piecewise_construct, make_tuple(name_1), make_tuple());
				s->nodes_with_links[name_1].push_back(link_for1);

				for (auto iter = s->nodes_with_links[link_for1._to].begin(); iter != s->nodes_with_links[link_for1._to].end(); ++iter) { // link ---
					link = *iter;
					if (link == link_mem) {
						edit = iter; 
					} 
				}
				s->nodes_with_links[link_for1._to].erase(edit);
				s->nodes_with_links.emplace(piecewise_construct, make_tuple(link_for1._to), make_tuple());
				s->nodes_with_links[link_for1._to].push_back(link_for2);
			}
			else { // найдена только одна вершина
				enter_link_data(link_for1.name_of_link, link_for1.type_link);
				link_for2.name_of_link = link_for1.name_of_link;
				link_for2.type_link = -link_for1.type_link;
				link_for2._to = name_1;

				for (auto iter = s->nodes_with_links[*it].begin(); iter != s->nodes_with_links[*it].end(); ++iter) {
					link = *iter;
					if (link.name_of_link == name_2 && link.type_link > 0) {
						edit = iter;
						link_for1._to = link._to;
						link_mem.name_of_link = link.name_of_link;
						link_mem.type_link = -link.type_link;
						link_mem._to = *it;
					}
				}
				s->nodes_with_links[*it].erase(edit); // link +++
				s->nodes_with_links.emplace(piecewise_construct, make_tuple(name_1), make_tuple());
				s->nodes_with_links[name_1].push_back(link_for1);

				for (auto iter = s->nodes_with_links[link_for1._to].begin(); iter != s->nodes_with_links[link_for1._to].end(); ++iter) { // link ---
					link = *iter;
					if (link == link_mem) {
						edit = iter;
					}
				}
				s->nodes_with_links[link_for1._to].erase(edit);
				s->nodes_with_links.emplace(piecewise_construct, make_tuple(link_for1._to), make_tuple());
				s->nodes_with_links[link_for1._to].push_back(link_for2);
			}
		} while (find_link == false);
	}
	else
		cout << "В сети нет связей\n\n";
}

void show_sem_set(Sem_set s) {
	string type;
	Link link;
	if (s.nodes.size() > 0) {
		for (auto it = s.nodes.begin(); it != s.nodes.end(); ++it)
		{
			if(s.nodes_with_links.count(*it) == 0)
			  cout << "Вершина без связи: " << *it << "\n";
			else {
				for (auto iter = s.nodes_with_links[*it].begin(); iter != s.nodes_with_links[*it].end(); ++iter) {
					link = *iter;
					if (link.type_link > 0) {
						type = show_name_link(link.type_link);
						cout << *it << " " << link.name_of_link << " (" << type << ") " << link._to << "\n";
					}
				}
			}
		}
		cout << "\n";
	}
	else
		cout << "Сеть не содержит данных\n\n";
}

void save_file(Sem_set s) {
	ofstream file;
	string filename;
	Link link;
	cout << "Введите имя файла для сохранения: ";
	cin >> filename;
	file.open(filename, fstream::out);
	file << s.nodes.size() << "\n";
	for (auto it = s.nodes.begin(); it != s.nodes.end(); ++it) {
		file << *it << "\n";
	}
	for (auto it = s.nodes.begin(); it != s.nodes.end(); ++it) {
		file << s.nodes_with_links[*it].size() << "\n";
		for (auto iter = s.nodes_with_links[*it].begin(); iter != s.nodes_with_links[*it].end(); ++iter) {
			link = *iter;
			file << link.name_of_link << "\n" << link.type_link << "\n" << link._to << "\n";
		}
	}
	file.close();
}

void open_file(Sem_set *s) {
	int node_count, links_count;
	ifstream file;
	string filename, name_node;
	Link link;
	cout << "Введите имя файла для сохранения: ";
	cin >> filename;
	file.open(filename, fstream::in);
	if (file) {
		file >> node_count;
		file.get();
		for (int i = 0; i < node_count; i++) {
			getline(file, name_node);
			s->nodes.emplace(name_node);
		}
		for (int i = 0; i < node_count; i++) {
			file >> links_count;
			file.get();
			for (int j = 0; j < links_count; j++) {
				auto it = s->nodes.begin();
				advance(it, i);
				file >> link.name_of_link;
				file >> link.type_link;
				file.get();
				file >> link._to;
				name_node = *it;
				s->nodes_with_links.emplace(piecewise_construct, make_tuple(name_node), make_tuple());
				s->nodes_with_links[name_node].push_back(link);
				it++;
			}
		}
		file.close();
	}
	else {
		file.close();
		cout << "Файл не найден\n\n";
	}
}

void show_path(vector<for_search> path, string start, Sem_set s) {
	string name_link;
	for_search src;
	cout << start;
	for (auto it = path.begin(); it != path.end(); ++it) {
		src = *it;
		name_link = show_name_link(src.type);
		cout << " (" << name_link << ") " << *next(s.nodes.begin(), src.vertex2);
	}
	cout << "\n";
}

int pos_links(Sem_set s, int position, int type) {
	Link link;
	int count = 0;
	auto it = s.nodes.begin();
	advance(it, position);
	for (auto iter = s.nodes_with_links[*it].begin(); iter != s.nodes_with_links[*it].end(); ++iter) {
		link = *iter;
		if (type == 1) {
			if (link.type_link > 0)
				count++;
		}
		else if(type == 2)
			count++;
	}
	return count;
}

void search(Sem_set s) {
	int dist1, dist2, cur, search_type, count_elem, find_count, possible, total, iter = 0;
	Link link;
	for_search src;
	vector<for_search> path;
	vector<vector<for_search>> matr;
	vector<int> passed;
	string ver1, ver2;
	bool end = false, new_ver = false, finded = false;

	count_elem = s.nodes.size();
	matr.resize(count_elem);

	int i = 0;
	for (auto it = s.nodes.begin(); it != s.nodes.end(); ++it) {
		if (s.nodes_with_links.count(*it) > 0) {
			for (auto iter = s.nodes_with_links[*it].begin(); iter != s.nodes_with_links[*it].end(); ++iter) {
				link = *iter;
				src.type = link.type_link;
				src.vertex1 = distance(s.nodes.begin(), it);
				src.vertex2 = distance(s.nodes.begin(), s.nodes.find(link._to));
				matr[i].push_back(src);
			}
		}
		i++;
	}

	cin.get();
	do {
		cout << "Введите имя вершины, в которой начинается путь: ";
		getline(cin, ver1);
		if (s.nodes.count(ver1) == 0)
			cout << "Данная вершина не найдена в сети\n";
	} while (s.nodes.count(ver1) == 0);
	dist1 = distance(s.nodes.begin(), s.nodes.find(ver1));

	do {
		cout << "Введите имя вершины, в которой заканчивается путь: ";
		getline(cin, ver2);
		if (s.nodes.count(ver2) == 0)
			cout << "Данная вершина не найдена в сети\n";
		if (ver1 == ver2)
			cout << "Данная вершина является началом пути, повторите ввод\n";
	} while (s.nodes.count(ver2) == 0 || ver1 == ver2);
	dist2 = distance(s.nodes.begin(), s.nodes.find(ver2));

	do {
		cout << "1) Поиск с учетом типа связи\n";
		cout << "2) Потенсивные связи\n";
		cout << "Введите вид поиска: ";
		cin >> search_type;
		if (search_type <= 0 || search_type > 2)
			cout << "Введен неверный тип связи, повторите попытку\n";
	} while (search_type <=0 || search_type > 2);
	cin.get();

	if (s.nodes_with_links.count(ver1) == 0)
		cout << "Из вершины '" << ver1 << "' нет пути\n";
	if (s.nodes_with_links.count(ver2) == 0)
		cout << "В вершину '" << ver2 << "' нет путей\n";
	else {
		cout << "\n";
		cur = dist1;
		passed.push_back(0);
		do {
			if (new_ver == true) {
				total = passed[iter];
			}
			else if (new_ver == false) {
				total = 0;
			}
			possible = pos_links(s, cur, search_type);
			finded = false;
		//	show_path(path, ver1, s);
		//	cout << "total=" << total << ", possible=" << possible <<"\n";
			if ((possible > total) && cur != dist2) { // если есть путь и не конец
			  find_count = 0;
			  int tmp = 0, tmp2 = matr[cur].size();
				do {
					src = matr[cur][find_count];
					auto it = find(path.begin(), path.end(), src);
					if (it == path.end()) {
						if (search_type == 1 && src.type > 0) {
							tmp++;
						}
						else if (search_type == 2) {
							tmp++;
						}
					}
					find_count++;
				} while (tmp <= total && find_count < tmp2);

				if (tmp > total)
					finded = true;
				if (finded == true) {
					path.push_back(src);
					passed[iter]++;
					passed.push_back(0);
					iter++;
					cur = src.vertex2;
					new_ver = false;
				}
			}

			if(finded == false) { // или нет пути, или конец, или начало
				int counter = 0;
				for (auto it = path.begin(); it != path.end(); ++it) {
					for_search z = *it;
					if (z.vertex1 == cur)
						counter++;
				}

				passed.pop_back();
				iter--;

				new_ver = true;
				if (cur == dist1 && path.size() == 0) { // если в начале без новых путей
					end = true;
				}
				else if (cur == dist2) {
					show_path(path, ver1, s);
					src = path.back();
					path.pop_back();
					if (path.size() > 0) {
						cur = src.vertex1;
					}
					else {
						cur = dist1;
					}
				}
				else {
					src = path.back();
					path.pop_back();
					if (path.size() > 0) {
						cur = src.vertex1;
					}
					else {
						cur = dist1;
					}
				}
			}
		} while (end == false); 
	}

	/*i = 0;
	cout << "\n";
	for (auto it = matr.begin(); it < matr.end(); ++it) {
		cout << i+1 << ": ";
		for (auto ite = matr[i].begin(); ite != matr[i].end(); ++ite) {
			for (auto iter = matr[i].begin(); iter != matr[i].end(); ++iter) {
				src = *iter; 
				cout << "[" << src.vertex1 << ", " << src.type << ", " << src.vertex2 << "] ";
			}
		}
		i++;
		cout << "\n";
	} */
	cout << "\n";
}

int main() {
	Sem_set sem_set;
	bool end = true;
	int cmd;
	setlocale(LC_ALL, "Ru");
	do {
		cout << "1) Добавление вершины в сеть\n";
		cout << "2) Удаление вершины из сети\n";
		cout << "3) Редактирование вершины в сети\n";
		cout << "4) Добавление связи в сеть\n";
		cout << "5) Удаление связи из сети\n";
		cout << "6) Редактирование связи в сети\n";
		cout << "7) Просмотреть содержимое сети\n";
		cout << "8) Сохранить содержимое сети\n";
		cout << "9) Открыть файл с сетью\n";
		cout << "10) Поиск связности понятий\n";
		cout << "11) Выход\n";
		cout << "Введите номер команды: ";
		cin >> cmd;
		cout << "\n";
		switch (cmd) {
		  case 1:
				add_node(&sem_set);
				break;

			case 2:
				delete_node(&sem_set);
				break;

			case 3:
				edit_node(&sem_set);
				break;

			case 4:
				add_link(&sem_set);
				break;

			case 5:
				delete_link(&sem_set);
				break;

			case 6:
				edit_link(&sem_set);
				break;

			case 7:
				show_sem_set(sem_set);
				break;

			case 8:
				save_file(sem_set);
				break;

			case 9:
				open_file(&sem_set);
				break;

			case 10:
				search(sem_set);
				break;

			case 11:
				end = false;
				break;

			default:
				cout << "Введена неизвестная команда, повторите попытку\n";
				break;
		}
	} while (end == true);
	return 0;
}