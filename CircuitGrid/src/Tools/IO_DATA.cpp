#include "IO_DATA.h"


//=============

/*
   nr_file_name: 0 = all*
				 1 = board,all*
				 2 = rec,all*
				 3 = josefistdumm,all*
*/


//std::string IO_DATA::choose_open_file() {//returns path to file
//	OPENFILENAMEA saveFileDialog;
//	char szSaveFileName[MAX_PATH] = "";
//	ZeroMemory(&saveFileDialog, sizeof(saveFileDialog));
//	saveFileDialog.lStructSize = sizeof(saveFileDialog);
//	saveFileDialog.hwndOwner = NULL;
//	saveFileDialog.lpstrFilter = "Josef ist dumm! (*.josefistdumm)\0*josefistdumm\0All Files (*.*)\0*.*\0";
//	saveFileDialog.lpstrFile = szSaveFileName;
//	saveFileDialog.nMaxFile = MAX_PATH;
//	saveFileDialog.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
//	saveFileDialog.lpstrDefExt = "josefistdumm";
//	GetOpenFileNameA(&saveFileDialog);
//	return saveFileDialog.lpstrFile;
//}

std::string IO_DATA::choose_open_file(int nr_file_name = 0) {//returns path to file
	OPENFILENAMEA openFileDialog;
	char szSaveFileName[MAX_PATH] = "";
	ZeroMemory(&openFileDialog, sizeof(openFileDialog));
	openFileDialog.lStructSize = sizeof(openFileDialog);
	openFileDialog.hwndOwner = NULL;

	openFileDialog.lpstrFilter = "All Files (*.*)\0*.*\0";
	openFileDialog.lpstrDefExt = "All";
	if (nr_file_name == 1) {
		openFileDialog.lpstrFilter = "Board (*.board)\0*board\0All Files (*.*)\0*.*\0";
		openFileDialog.lpstrDefExt = "board";
	}
	else if (nr_file_name == 2) {
		openFileDialog.lpstrFilter = "Recording (*.rec)\0*rec\0All Files (*.*)\0*.*\0";
		openFileDialog.lpstrDefExt = "rec";
	}
	else if (nr_file_name == 3) {
		openFileDialog.lpstrFilter = "Josef ist dumm! (*.josefistdumm)\0*josefistdumm\0All Files (*.*)\0*.*\0";
		openFileDialog.lpstrDefExt = "josefistdumm";
	}
	openFileDialog.lpstrFile = szSaveFileName;
	openFileDialog.nMaxFile = MAX_PATH;
	openFileDialog.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
	if (!GetOpenFileNameA(&openFileDialog))
		return "";
	return openFileDialog.lpstrFile;

}


std::string IO_DATA::choose_save_file(int nr_file_name = 0) {
	OPENFILENAMEA saveFileDialog;
	char szSaveFileName[MAX_PATH] = "";
	ZeroMemory(&saveFileDialog, sizeof(saveFileDialog));
	saveFileDialog.lStructSize = sizeof(saveFileDialog);
	saveFileDialog.hwndOwner = NULL;

	saveFileDialog.lpstrFilter = "All Files (*.*)\0*.*\0";
	saveFileDialog.lpstrDefExt = "All";
	if (nr_file_name == 1) {
		saveFileDialog.lpstrFilter = "Board (*.board)\0*board\0All Files (*.*)\0*.*\0";
		saveFileDialog.lpstrDefExt = "board";
	}
	else if (nr_file_name == 2) {
		saveFileDialog.lpstrFilter = "Recording (*.rec)\0*rec\0All Files (*.*)\0*.*\0";
		saveFileDialog.lpstrDefExt = "rec";
	}
	else if (nr_file_name == 3) {
		saveFileDialog.lpstrFilter = "Josef ist dumm! (*.josefistdumm)\0*josefistdumm\0All Files (*.*)\0*.*\0";
		saveFileDialog.lpstrDefExt = "josefistdumm";
	}

	saveFileDialog.lpstrFile = szSaveFileName;
	saveFileDialog.nMaxFile = MAX_PATH;
	saveFileDialog.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
	if (!GetSaveFileNameA(&saveFileDialog))
		return "";
	return saveFileDialog.lpstrFile;
}


bool IO_DATA::save_to_file(std::string file_name, const char *output_data, const int data_size, bool append_data) {
	if (file_name == "")
		return false;

	auto myfile = std::fstream(file_name, std::ios::out | std::ios::binary | (append_data ? std::ios_base::app : 0));
	myfile.write((char*)output_data, data_size);
	myfile.close();
	return true;

}

bool IO_DATA::read_from_file(std::string file_name, std::vector<char>& input_data) {
	if (file_name == "")
		return false;
	std::ifstream input(file_name, std::ios::binary);
	input_data = std::vector<char>((std::istreambuf_iterator<char>(input)), (std::istreambuf_iterator<char>()));
	input.close();
	return true;
}

//=============