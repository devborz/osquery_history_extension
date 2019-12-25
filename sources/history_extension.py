import json
import osquery
from os.path import expanduser

@osquery.register_plugin
class MyTablePlugin(osquery.TablePlugin):
    def name(self):
        return "vimplugins"
    def columns(self):
        return [
            osquery.TableColumn(name="Plugin Name", type=osquery.STRING),
            osquery.TableColumn(name="Github Stars", type=osquery.STRING),
            osquery.TableColumn(name="VimAwesome Category", type=osquery.STRING),
            osquery.TableColumn(name="Open Issues", type=osquery.STRING),
            osquery.TableColumn(name="Closed Issues", type=osquery.STRING),
        ]
    def generate(self, context):
        query_data = []
        home = expanduser("~")
        input_file = open(home + '/.vimPlugins.json')
        json_array = json.load(input_file)
        for item in json_array:
            row = {}
            row["Plugin Name"] = item['name']
            row["Github Stars"] = item['stars']
            row["VimAwesome Category"] = item['category']
            row["Open Issues"] = item['open']
            row["Closed Issues"] = item['closed']
            query_data.append(row)
        return query_data

if __name__ == "__main__":
    osquery.start_extension(name="vim_info", version="1.0.0")
