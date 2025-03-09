#include "Test.h"

std::string Test::generate_message(char const* const condition, size_t const line, bool const pass) const
{
	std::ostringstream oss;
	oss << "[" << (pass ? "PASS" : "FAIL") << "] " << line << ": " << currentName << " (" << condition << ")";
	return oss.str();
}

void Test::capture_output()
{
#ifndef PRINT_OUTPUT
	std::cout.rdbuf(outputStream.rdbuf()); std::cerr.rdbuf(outputStream.rdbuf());
#endif // PRINT_OUTPUT
}

void Test::restore_output()
{
#ifndef PRINT_OUTPUT
	std::cout.rdbuf(coutBuf); std::cerr.rdbuf(cerrBuf);
#endif // PRINT_OUTPUT
}

void Test::set_category(char const* const categoryName)
{
	currentCategoryName = categoryName;
	restore_output();
	auto found = categories.find(currentCategoryName);
	if (found == categories.end())
	{
		currentCategoryIndex = static_cast<int>(categories.size());
		categories.emplace(currentCategoryName, currentCategoryIndex);
		categoryNames.push_back(currentCategoryName);
		std::cout << currentCategoryName << "\r";
	}
	else
	{
		currentCategoryIndex = found->second;
	}
	capture_output();
}

void Test::set_test(char const* const testName)
{
	currentName = testName;
	auto found2 = results.find(currentCategoryIndex);
	if (found2 == results.end())
	{
		results.emplace(currentCategoryIndex, Results());
		currentResults = &results[currentCategoryIndex];
	}
	else
	{
		currentResults = &found2->second;
	}
}

void Test::pass(char const* const condition, size_t const line)
{
	std::string message = generate_message(condition, line, true);
	currentResults->add_message(message, Results::MessageType::Pass);
	passCount++;
}

void Test::fail(char const* const condition, size_t const line)
{
	std::string message = generate_message(condition, line, false);
	currentResults->add_message(message, Results::MessageType::Fail);
	failCount++;
}

void Test::write_message(std::string const& message)
{
	currentResults->add_message(std::string("[    ] ").append(message), Results::MessageType::Generic);
}

void Test::save_results(std::filesystem::path const& path) const
{
	// generate the results table string
	std::fstream file(path, std::ios::out);

	if (!file.is_open())
	{
		std::cerr << "Failed to open file: " << path << std::endl;
		return;
	}

	int const CATEGORY_NAME_WIDTH = 30;
	int const PASS_COUNT_WIDTH = 8;
	int const FAIL_COUNT_WIDTH = 8;
	int const MESSAGE_WIDTH = 128;
	int const RESULT_WIDTH = 6;

	file << std::left;

	// create header
	double passRate = get_pass_rate();
	file << "# Results\n"
		<< passCount << "/" << passCount + failCount << " (" << std::fixed << std::setprecision(2) << passRate << "%)\n";

	if (failCount > 0)
	{
		file << failCount << " failures.\n";
	}

	// create summary
	file << "\n## Summary\n"
		<< "| " << std::setw(CATEGORY_NAME_WIDTH) << "Category" << " | " << std::setw(PASS_COUNT_WIDTH) << "Passes" << " | " << std::setw(FAIL_COUNT_WIDTH) << "Fails" << " |\n"
		<< "| " << std::string(CATEGORY_NAME_WIDTH, '-') << " | " << std::string(PASS_COUNT_WIDTH, '-') << " | " << std::string(FAIL_COUNT_WIDTH, '-') << " |\n";

	for (auto const& categoryName : categoryNames)
	{
		int categoryIndex = categories.at(categoryName);
		Results const& categoryResults = results.at(categoryIndex);

		file << "| " << std::left << std::setw(CATEGORY_NAME_WIDTH) << categoryName << " | " << std::right << std::setw(PASS_COUNT_WIDTH) << categoryResults.get_pass_count() << " | " << std::setw(FAIL_COUNT_WIDTH) << categoryResults.get_fail_count() << " |\n";
	}

	file << std::left;

	// create fails
	file << "\n## Failures\n";

	if (failCount == 0)
	{
		// no failures
		file << "No failures! :)\n";
	}
	else
	{
		// list failures
		file << "| " << std::setw(CATEGORY_NAME_WIDTH) << "Category" << " | " << std::setw(MESSAGE_WIDTH) << "Message" << " |\n"
			<< "| " << std::string(CATEGORY_NAME_WIDTH, '-') << " | " << std::string(MESSAGE_WIDTH, '-') << " |\n";

		for (auto const& categoryName : categoryNames)
		{
			int categoryIndex = categories.at(categoryName);
			Results const& categoryResults = results.at(categoryIndex);

			for (size_t const failIndex : categoryResults.get_fails())
			{
				std::string const& message = categoryResults.get_message(failIndex);
				file << "| " << std::setw(CATEGORY_NAME_WIDTH) << categoryName << " | " << std::setw(MESSAGE_WIDTH) << message << " |\n";
			}
		}
	}

	// create all messages, broken up by category
	file << "\n# Categories\n";

	for (auto const& categoryName : categoryNames)
	{
		int categoryIndex = categories.at(categoryName);
		Results const& categoryResults = results.at(categoryIndex);
		file << "\n## " << categoryName << "\n"
			<< "| " << std::setw(RESULT_WIDTH) << "Result" << " | " << std::setw(MESSAGE_WIDTH) << "Message" << " |\n"
			<< "| " << std::string(RESULT_WIDTH, '-') << " | " << std::string(MESSAGE_WIDTH, '-') << " |\n";

		for (auto const& message : categoryResults.get_messages())
		{
			file << "|  " << message.substr(1, 4) << "  | " << std::setw(MESSAGE_WIDTH) << message.substr(7) << " |\n";
		}
	}

	file.close();

	std::cout << "Results saved to: " << path << std::endl;
}
