#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#define BUFFSIZE 1000

bool check_image_size (std::string, char*);
bool is_bmp (std::string, char* );
bool compare_image (std::string, std::ifstream*);

struct Param_image {
	int type;
	int width;
	int height;
};	

class Image_file {
	public:
	std::ifstream image_database;
	std::ifstream reference_image;

	void open(char* , char* ); 
	bool check(); 
	Image_file(void);
	Image_file(char* , char* );
	void close();

	private:
	std::string filename_database;
	std::string filename_reference;
	bool err_data;
	bool err_im;
};		

int main(int argc, char** argv)
{	
	char buff[BUFFSIZE];
	std::string path_to_image; 
	bool flag = false;
		
	if (argc != 3) { 
		std::cerr << "Invalid number of parameters\n";
		exit(2);
	}
	Image_file compare_files(argv[1], argv[2]);
	if (!compare_files.check())
		exit(0);	
	compare_files.reference_image.getline(buff, BUFFSIZE);
	while ( compare_files.image_database >> path_to_image){ 
		if(!is_bmp(path_to_image, buff))
			continue;		
		if (!check_image_size(path_to_image, buff)) 
			continue;
 		if (flag = compare_image(path_to_image, &compare_files.reference_image))
			break;
	}
	if(flag)
		std::cout << path_to_image;
	else
		std::cout << "file not found" << std::endl;

	compare_files.close();
	return 0;
}

void Image_file::open(char* image_data, char* reference_im) 
{
	err_data = true;
 	err_im = true;
	filename_database = image_data;
	filename_reference = reference_im;
	image_database.open(filename_database, std::ios_base::in);
	if (!image_database.is_open())
		err_data = false;
	reference_image.open(filename_reference, std::ios_base::in |
 	std::ios_base::binary);
	if (!reference_image.is_open())
		err_im = false;	
}
	
bool Image_file::check() 
{
	bool flag = true;
	if (!err_data) {
		std::cerr << "File " << filename_database << " not found\n";
		flag = false;
	}
	else if (!err_im) {
		std::cerr << "File " << filename_reference << " not found\n";
		flag = false;
	}
	return flag;
}
			
	
Image_file::Image_file(void) 
{
	err_data = false;
 	err_im = false;
}

Image_file::Image_file(char* image_data, char* reference_im) 
{
	open(image_data, reference_im);
}
	
void Image_file::close()
{
	image_database.close();
 	reference_image.close();
}

//Функция проверки размеров изображений
//path_to_image путь к изображению из базы
//buff_2 набор битов с хедером BMP файла
//Только для версий выше CORE
bool check_image_size(std::string path_to_image, char* buff_2)
{
	std::ifstream check_image(path_to_image,
      	std::ios_base::in | std::ios_base::binary);
	char buff_1[BUFFSIZE];
	Param_image size_1;
	Param_image size_2;

      	check_image.getline(buff_1, BUFFSIZE);

      	size_1.width = 1 * buff_1[12] + 2 * buff_1[13]
       	+ 3 * buff_1[14] + 4 * buff_1[15];
       	size_2.width = 1 * buff_2[12] + 2 * buff_2[13]
      	+ 3 * buff_2[14] + 4 * buff_2[15];
    	if (size_1.width != size_2.width)
    		return false;

	size_1.height = 1 * buff_1[16] + 2 * buff_1[17]
	+ 3 * buff_1[18] + 4 * buff_1[19];
	size_2.height = 1 * buff_2[16] + 2 * buff_2[17]
	+ 3 * buff_2[18] + 4 * buff_2[19];
	
	if (size_1.height != size_2.height)
             	return false;
       	check_image.close();
	return true;
}

//Функция проверки соответствия типов изображений
bool is_bmp(std::string path_to_image, char* buff_2)
{
	std::ifstream check_image(path_to_image,
	std::ios_base::in | std::ios_base::binary);
	char buff_1[BUFFSIZE];
	Param_image type_1;
	Param_image type_2;

	check_image.getline(buff_1, BUFFSIZE);
	type_1.type = buff_1[0] + buff_1[1];
	type_2.type = buff_2[0] + buff_2[1];	

	if (type_1.type != type_2.type)
		return false;
	return true;
} 

//Проверка цветов изображения
bool compare_image(std::string path_to_image, std::ifstream* reference_image)
{
	std::ifstream check_image(path_to_image,
	std::ios_base::in | std::ios_base::binary);
	char buff_1[BUFFSIZE];
	char buff_2[BUFFSIZE];
	int byte = 138;      //Начало таблицы цветов	

	while (!reference_image->eof() || !check_image.eof()) {
		check_image.getline(buff_1, BUFFSIZE);
		reference_image->getline(buff_2, BUFFSIZE);

		for( ; byte <= BUFFSIZE ; byte ++) {				
			if (buff_1[byte] != buff_2[byte]);
				return false;
		} 
	}
	return true;
}

