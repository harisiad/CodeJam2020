#include <iostream>
#include <regex>
#include <vector>
#include <sstream>
#include <limits>

struct task
{
	std::string initial{};
	int start;
	int end;
};

std::string createPlan(std::vector<task>& tasks)
{
	char person = 'J';
	std::string taskAssignement{ "" };
	std::vector<int> unassignedTasks;

	tasks[0].initial = person;
	for (int i = 0; i < tasks.size(); ++i)
	{
		if (tasks[i].initial == "J")
		{
			for (int j = i + 1; j < tasks.size(); ++j)
			{
				if (tasks[j].start >= tasks[i].end ||
					tasks[j].end <= tasks[i].start)
				{
					tasks[j].initial = person;
				}
				else
				{
					unassignedTasks.push_back(j);
				}
			}
		}
	}

	if (!unassignedTasks.empty())
	{
		person = 'C';
		tasks[unassignedTasks.front()].initial = person;
		
		for (int i = 0; i < unassignedTasks.size(); ++i)
		{
			for (int j = i + 1; j < unassignedTasks.size(); ++j)
			{
				if (tasks[unassignedTasks[j]].start >= tasks[unassignedTasks[i]].end ||
					tasks[unassignedTasks[j]].end <= tasks[unassignedTasks[i]].start)
				{
					tasks[unassignedTasks[j]].initial = person;
				}
			}
		}
	}

	for (auto task : tasks)
	{
		taskAssignement += task.initial;
	}

	if (taskAssignement.size() < tasks.size())
	{
		taskAssignement = "IMPOSSIBLE";
	}

	return taskAssignement;
}

int main()
{
	std::cout << "Parenting Partnering" << "\n";

	int i_noTestCases{ 0 };
	int i_noTasks{ 0 };
	std::regex pat{ R"([0-9]+)" };
	std::vector<task> tasks;
	std::vector<std::string> result;

	std::cout << "Number of test cases: ";
	std::cin >> i_noTestCases;

	for (int tCase = 0; tCase < i_noTestCases; ++tCase)
	{
		std::cout << "Number of tasks: ";
		std::cin >> i_noTasks;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		for (int i_task = 0; i_task < i_noTasks; ++i_task)
		{
			std::string line;
			int count = 0;

			std::getline(std::cin, line);
			std::vector<int> v_task;

			task t{ "", 0, 0 };
			std::stringstream(line.substr(0, line.find(" "))) >> t.start;
			std::stringstream(line.substr(line.find(" ") + 1, line.size())) >> t.end;

			tasks.push_back(t);
		}
		result.push_back(createPlan(tasks));
		tasks.clear();
	}

	for (int tCase = 0; tCase < i_noTestCases; ++tCase)
	{
		std::cout << "Case #" << tCase << " " << result[tCase] << "\n";
	}
}

