import json
import osquery
from os.path import expanduser

@osquery.register_plugin
class FilesystemHistoryTablePlugin(osquery.TablePlugin):
    def name(self):
        return "filesystem_history"
    def columns(self):
        return [
            osquery.TableColumn(name="Time", type=osquery.STRING),
            osquery.TableColumn(name="Path", type=osquery.STRING),
            osquery.TableColumn(name="Filename", type=osquery.STRING),
        ]
    def generate(self, context):
        query_data = []
        home = expanduser("~")
        input_file = open(home+'/fs_history.json')
        json_array = json.load(input_file)
        for item in json_array:
            row = {}
            row["Time"] = item['time']
            row["Path"] = item['path']
            row["Filename"] = item['filename']
            query_data.append(row)
        return query_data

@osquery.register_plugin
class BashHistoryTablePlugin(osquery.TablePlugin):
    def name(self):
        return "bash_history"
    def columns(self):
        return [
            osquery.TableColumn(name="Time", type=osquery.STRING),
            osquery.TableColumn(name="Execute directory", type=osquery.STRING),
            osquery.TableColumn(name="Command", type=osquery.STRING),
        ]
    def generate(self, context):
        query_data = []
        home = expanduser("~")
        input_file = open(home +'/bash_history.json')
        json_array = json.load(input_file)
        for item in json_array:
            row = {}
            row["Time"] = item['time']
            row["Execute directory"] = item['path']
            row["Command"] = item['command']
            query_data.append(row)
        return query_data

@osquery.register_plugin
class VimCommandlineHistoryTablePlugin(osquery.TablePlugin):
    def name(self):
        return "vim_commandline_history"
    def columns(self):
        return [
            osquery.TableColumn(name="Time", type=osquery.STRING),
            osquery.TableColumn(name="Command", type=osquery.STRING),
        ]
    def generate(self, context):
        query_data = []
        home = expanduser("~")
        input_file = open(home +'/vim_cmd_history.json')
        json_array = json.load(input_file)
        for item in json_array:
            row = {}
            row["Time"] = item['time']
            row["Command"] = item['command']
            query_data.append(row)
        return query_data

@osquery.register_plugin
class vimFileMarksHistoryTablePlugin(osquery.TablePlugin):
    def name(self):
        return "vim_filemarks_history"
    def columns(self):
        return [
            osquery.TableColumn(name="Time", type=osquery.STRING),
            osquery.TableColumn(name="File's path", type=osquery.STRING),
            osquery.TableColumn(name="Filename", type=osquery.STRING),
            osquery.TableColumn(name="Position Row", type=osquery.STRING),
            osquery.TableColumn(name="Position Column", type=osquery.STRING),
        ]
    def generate(self, context):
        query_data = []
        home = expanduser("~")
        input_file = open(home +'/vim_cmd_history.json')
        json_array = json.load(input_file)
        for item in json_array:
            row = {}
            row["Time"] = item['time']
            row["File's path"] = item['path']
            row["Filename"] = item['filename']
            row["Command"] = item['row']
            row["Command"] = item['column']
            query_data.append(row)
        return query_data

if __name__ == "__main__":
    osquery.start_extension(name="history", version="1.0.0")
