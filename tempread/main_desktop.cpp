#include <iostream>
#include <fstream>
#include <string>

class AppContext {
public:
    int num = 0;
    const std::string path = "./user_data.txt";

    void run_file_operations() {
        std::ifstream inFile(path);
        if (inFile.is_open()) {
            std::cout << "[C++] 기존에 저장된 데이터 읽기 성공:" << std::endl;
            inFile >> num;
            inFile.close();
        } else {
            std::cout << "[C++] 저장된 데이터가 없습니다. 새로 만듭니다." << std::endl;
            num = 0;
        }

        std::cout << "현재 인스턴스의 값: " << num << std::endl;
        num += 1;

        std::ofstream outFile(path);
        if (outFile.is_open()) {
            outFile << num;
            outFile.close();
            std::cout << "[C++] 파일 쓰기 완료. 다음 값: " << num << std::endl;
        }
    }
};

int main() {
    AppContext* app = new AppContext();
    app->run_file_operations();
    delete app;
    return 0;
}
