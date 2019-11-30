#include <osquery/sdk.h>

using namespace osquery;

// Note 2: Define at least one plugin or table.
class ExampleTablePlugin : public TablePlugin {
 private:
  TableColumns columns() const override {
    return {
      std::make_tuple("example_text", TEXT_TYPE, ColumnOptions::DEFAULT),
      std::make_tuple("example_integer", INTEGER_TYPE, ColumnOptions::DEFAULT),
    };
  }

  QueryData generate(QueryContext& request) override {
    QueryData results;
    Row r;

    r["example_text"] = "example";
    r["example_integer"] = INTEGER(1);
    results.push_back(r);
    return results;
  }
};

// Note 3: Use REGISTER_EXTERNAL to define your plugin or table.
REGISTER_EXTERNAL(ExampleTablePlugin, "table", "History");

int main(int argc, char* argv[]) {
  // Note 4: Start logging, threads, etc.
  osquery::Initializer runner(argc, argv, ToolType::EXTENSION);

  // Note 5: Connect to osqueryi or osqueryd.
  auto status = startExtension("example", "0.0.1");
  if (!status.ok()) {
    LOG(ERROR) << status.getMessage();
    runner.requestShutdown(status.getCode());
  }

  // Finally, shutdown.
  runner.waitForShutdown();

  return 0;
}
