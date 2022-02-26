#pragma once
#include<vector>
#include<map>
#include<algorithm>

template <typename T>
class node {
public:
	std::vector<int> connects;
	T data;
};

template <typename T>
class graph {
private:
	std::map<int, node<T>> value;

public:
	void add(int num, T data) {
		value.insert(std::pair<int, node<T>>(num, { {}, data }));
	}

	void change(int num, T data) {
		value[num] = { value[num].connects,data};
	}

	void connect(int a, int b) {
		value[a].connects.push_back(b);
		value[b].connects.push_back(a);
	}

	void deconnect(int a, int b) {
		auto& aCon = value[a].connects;
		auto& bCon = value[b].connects;

		aCon.erase(std::find(aCon.begin(), aCon.end(), b));
		bCon.erase(std::find(bCon.begin(), bCon.end(), a));
	}

	node<T> getNode(int index) {
		return value[index];
	}

	std::vector<int> getConnect(int index) {
		std::map<int, bool> goingNode;
		std::vector<int> togoNode = {index};
		std::vector<int> returnVal;

		while (togoNode.size()) {
			int nowIndex = togoNode.front();

			if (goingNode.find(nowIndex) == goingNode.end()) {
				goingNode[nowIndex] = true;
				returnVal.push_back(nowIndex);

				for (auto element : value[nowIndex].connects)
					togoNode.push_back(element);
			}

			togoNode.erase(togoNode.begin());
		}

		return returnVal;
	}

	int getSize() {
		return value.size();
	}
};

namespace graphManage {

	template<typename T, typename fun>
	void foreach(graph<T> & myGraph,std::vector<int> myNodes, fun func) {
		for (auto element : myNodes)
			myGraph.change(element,func(myGraph.getNode(element).data));
	}
}
