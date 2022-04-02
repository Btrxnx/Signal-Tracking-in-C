//KHAI BÁO CÁC THƯ VIỆN CẦN SỬ DỤNG
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<stddef.h>
#include<math.h>

//KHAI BÁO TÊN FILE VÀ HẰNG SỐ
#define FILENAME "log.txt"
#define MAXLENGTHFILE 5000

//KHAI BÁO CÁC HÀM NGUYÊN MẪU
void strlw(char *xau);
char fileStr[MAXLENGTHFILE];
int soBanTinGuiDi (char* str);
int soBanTinTuThietBi (char* str); 
int soCongtac(char* str);
int soBanTinGuiLoi(char* str);
int thoiGianTreLonNhat(char* str);
int thoiGianTreTrungBinh(char* str);

//HÀM CHÍNH
int main() {

    soBanTinGuiDi(fileStr);
    soBanTinTuThietBi(fileStr);
    soCongtac (fileStr);
    soBanTinGuiLoi(fileStr);
    thoiGianTreLonNhat(fileStr);
    thoiGianTreTrungBinh(fileStr);
    
     return 0;
} 

//*****************************************************************************************************************************************
// CÁC HÀM TRONG CHƯƠNG TRÌNH:

//HÀM ĐỔI KÍ TỰ TRONG CHUỖI TỪ IN HOA THÀNH KÍ TỰ THƯỜNG
void strlwr(char *xau) {                                //Hàm được dùng trong hàm soBanTinTuThietBi
    for(int i=0;i<strlen(xau);i++) {
        xau[i]=tolower(xau[i]);                         //Hàm tolower dùng để thay đổi kí tự in hoa sang kí tự thường
    }
}

//HÀM TÍNH SỐ BẢN TIN GỬI ĐI TRONG THỜI GIAN LOG
int soBanTinGuiDi (char* str) {
    int status;
    FILE * fp = NULL;

    fp = fopen(FILENAME, "r");
    if (fp == NULL) {
        printf("File does not exist\n");
        return -1;
    }
    status = fread(str, MAXLENGTHFILE, 1, fp);

    char* token;                                                    
    char* ret = NULL;
    int count = 0;
    token = strtok(str, "\n");                                      //Hàm strtok() dùng để phân tách chuỗi str thành các hàng dựa vào chuỗi \n
    while (token != NULL) {
        ret = strstr(token, "\"cmd\":\"set\"");                     //Hàm strstr() dùng để tìm kiếm chuỗi\"cmd\":\"set\" qui định cho số bản tin gửi đi
        if (ret != NULL) {
            printf("%s\n", token);
            count++;
        }
        token = strtok(NULL,"\n");                                  //Gán cho token giá trị NULL để xóa chuỗi thông tin vừa xử lí và chuẩn bị để chuỗi thông tin mới được nạp vào
    }
    printf("So ban tin: %d\n", count);
    
    fclose(fp);
    fp = NULL;
    return status;
    
}

//HÀM TÍNH SỐ BẢN TIN GỬI ĐI TỪ THIẾT BỊ
int soBanTinTuThietBi (char* str) {
    int status;
    FILE * fp = NULL;

    fp = fopen(FILENAME, "r");
    if (fp == NULL) {
        printf("File does not exist\n");
        return -1;
    }
    status = fread(str, MAXLENGTHFILE, 1, fp);
   
   char* token;
   char* ret = NULL;
   int count = 0;
   char address[5];
   token = strtok(str, "\n");
   printf("Nhap dia chi: \n");                                                    
   scanf("%s", address);                                                        //Địa chỉ thiết bị được người dùng nhập vào để tìm kiếm bản tin
   strlwr(address);
    while (token != NULL ) {
        ret = strstr(token, "\"cmd\":\"set\"");
        if (ret != NULL) {
            ret = strstr(token, address);                                       //Tìm địa chỉ thiết bị và gán vào ret
            if (ret != NULL) {
                printf("%s\n", token);
                count++;
            }
                
        }
        token = strtok(NULL,"\n");
    }
    printf("So ban tin gui di la: %d\n", count);
    
    fclose(fp);
    fp = NULL;
    return status;
}

//HÀM TÍNH SỐ CÔNG TẮC VỚI MỖI ĐỊA CHỈ NETWORK VÀ ENDPOINT
int soCongtac(char* str) {
    int status;
    FILE * fp = NULL;

    fp = fopen(FILENAME, "r");
    if (fp == NULL) {
        printf("File does not exist\n");
        return -1;
    }
    status = fread(str, MAXLENGTHFILE, 1, fp);

    char Nwk[6];
    char Endpoint[2];
    char tempNwk[6];
    Nwk[4] = '\0';                                                                                          //Gán lần lượt \0 cho các chuỗi Nwk, Endpoint, tempNwk để không in ra phần thừa nằm ngoài chuỗi
    Endpoint[1] = '\0';
    tempNwk[4] = '\0';
    int i = 0;
    int isAvailable = 0;
    char* token;
    char* ret;
    token = strtok(str, "\n");
    while (token != NULL) {
        //Xác định lần lượt các bản tin và địa chỉ trong log.txt bằng các xâu "switch" và "data"
        ret = strstr(token, "switch");
        if (ret != NULL) {
            ret = strstr(ret, "data");
            if (ret != NULL) {
                if (i==0) {
                    //Lưu giá trị Network và Endpoint vào các chuỗi Nwk[], Endpoint[]
                    memcpy(Nwk, &ret[14],4);                                                               //Hàm memcpy dùng để gán bộ nhớ tới Nwk từ địa chỉ &ret[14] được trỏ tới với số lượng nhất bit được xác định là 4                               
                    memcpy(Endpoint, &ret[21],1);                                                          //Lưu giá trị Endpoint là giá trị ở vị trí 21 của chuỗi ret
                    printf("thiet bi %d co dia chi la: NWK - %s, ENDPOINT - %s \n", i+1, Nwk,Endpoint);
                    i++;
                }
            else {
                    memcpy(tempNwk, &ret[14],4);
                    //So sánh địa chỉ chuỗi Nwk và các chuỗi khác
                    if(strcmp(Nwk,tempNwk)==0) {                                                            //So sánh 2 chuỗi kí tự bằng hàm strcmp
                        isAvailable = 0;
                    }
                    else {
                        isAvailable = 1;
                    }
                }
                //Hai chuỗi khác nhau thì in ra chuỗi Network mới vừa tim được với Endpoint mới
                if (isAvailable == 1) {                                                                     
                    memcpy(Nwk,tempNwk,5);
                    memcpy(Endpoint, &ret[21],1);
                    printf("thiet bi %d co dia chi la: NWK - %s, ENDPOINT - %s \n",i+1,Nwk,Endpoint);
                    i++;
                    isAvailable = 0;
                    }
            }
            }
        token = strtok(NULL, "\n");
    }

    fclose(fp);
    fp = NULL;
    return status;
}

//HÀM TÍNH SỐ BẢN TIN GỬI ĐI BỊ LỖI
int soBanTinGuiLoi(char* str) {
    int status;
    FILE * fp = NULL;

    fp = fopen(FILENAME, "r");
    if (fp == NULL) {
        printf("File does not exist\n");
        return -1;
    }
    status = fread(str, MAXLENGTHFILE, 1, fp);

    int i = 0;
    char tin[4], tinle[4];
    char* token;
    char* ret = NULL;
    int error = 0;

    token = strtok(str, "\n");

    while (token != NULL ) {
        //Xác định xâu "requid" trong bản tin
        ret = strstr(token, "reqid");
        if (ret != NULL) {
            //Xác định và lưu giá trị reqid bản tin lẻ
            if(i % 2 == 0) {
                memcpy(tin, &ret[9], 4);
            }
            //Xác định và lưu giá trị reqid bản tin chẵn
            else {
                memcpy(tinle, &ret[9],4);
                //So sánh giá trị reqid của 2 bản tin, nếu khác nhau thì bản cặp bản tin gửi và phản hồi đó bị lỗi 
                int temp = memcmp(tin, tinle, 4);
                if (temp != 0) {
                    error++;
                }
            }  
            i++;  
        }
        token = strtok(NULL,"\n");
    }
    printf("So ban tin loi: %d\n", error);

    fclose(fp);
    fp = NULL;
    return status;
}

//HÀM TÍNH THỜI GIAN TRỄ LỚN NHẤT GIỮA BẢN TIN GỬI ĐI VÀ BẢN TIN PHẢN HỒI
int thoiGianTreLonNhat(char* str) {
    int status;
    FILE * fp = NULL;

    fp = fopen(FILENAME, "r");
    if (fp == NULL) {
        printf("File does not exist\n");
        return -1;
    }
    status = fread(str, MAXLENGTHFILE, 1, fp);

    int i = 0;
    char thoigian_gui[22], thoigian_den[22], tin[4], tinle[4], phut_gui[4], phut_den[4], giay_gui[8], giay_den[8];
    phut_gui[3] = '\0';
    phut_den[3] = '\0';
    giay_gui[7] = '\0';
    giay_den[7] = '\0';
    char* token;
    char* ret = NULL;
    char* ret_tin = NULL;
    double maxdelay = 0;
    double delay = 0;
    int diff = 0;
    token = strtok(str, "\n");

    while (token != NULL ) {
        ret = strstr(token, "INFO");
        ret_tin = strstr(token,"reqid");
        if (ret != NULL) {
            if(i % 2 == 0) {
                memcpy(thoigian_gui, &ret[6], 22);                          //Tách thời gian gửi từ bản tin chẵn
                memcpy(tin, &ret_tin[9], 4);                                //Tách giá trị requid từ bản tin chẵn

            }
            else {
                memcpy(thoigian_den, &ret[6],22);                           //Tách thời gian đến từ bản tin lẻ
                memcpy(tinle, &ret_tin[9], 4);                              //Tách giá trị reqid từ bản tin lẻ
                int error = memcmp(tin, tinle, 4);                          //So sánh 2 giá trị reqid từ 2 bản tin nhằm loại từ các cặp bản tin lỗi
                
                if (error == 0 ) {
                //Tách các chuỗi phút và giây trong chuỗi thời gian
                memcpy(phut_gui, &thoigian_gui[13], 2);
                memcpy(phut_den, &thoigian_den[13], 2);
                memcpy(giay_gui, &thoigian_gui[16], 6);
                memcpy(giay_den, &thoigian_den[16], 6);
                //Chuyển đổi các chuỗi phút và giây thành số và tính thời gian delay
                diff = memcmp(phut_gui,phut_den,2);
                if (diff != 0) {
                    delay = (atof(phut_den) - atof(phut_gui))* 60000 + ((atof(giay_den) - atof(giay_gui))*1000);            //Hàm atof dùng để chuyển đổi kí tự số thành số dạng double
                }
                else {
                    delay = (atof(giay_den) - atof(giay_gui))*1000;
                }
                }
                if (delay > maxdelay) {
                maxdelay = delay;
            }
            }  
            i++;  
        }
        token = strtok(NULL,"\n");
    }
    printf("Do tre lon nhat la: %.lf Millisecond\n", maxdelay);

    fclose(fp);
    fp = NULL;
    return status;
}

//HÀM TÍNH THỜI GIAN TRỄ TRUNG BÌNH TRONG KHOẢNG THỜI GIAN LOG
int thoiGianTreTrungBinh(char* str) {
    int status;
    FILE * fp = NULL;

    fp = fopen(FILENAME, "r");
    if (fp == NULL) {
        printf("File does not exist\n");
        return -1;
    }
    status = fread(str, MAXLENGTHFILE, 1, fp);

    //Hàm tương tự như hàm thoiGianTreLonNhat() những thay tìm maxdelay bằng avgdelay
    int i = 0;
    char thoigian_gui[22], thoigian_den[22], tin[4], tinle[4], phut_gui[4], phut_den[4], giay_gui[8], giay_den[8];
    phut_gui[3] = '\0';
    phut_den[3] = '\0';
    giay_gui[7] = '\0';
    giay_den[7] = '\0';
    char* token;
    char* ret = NULL;
    char* ret_tin = NULL;
    double avg_delay = 0;
    double delay = 0;
    int diff = 0;
    int count = 0;
    token = strtok(str, "\n");

    while (token != NULL ) {
        ret = strstr(token, "INFO");
        ret_tin = strstr(token,"reqid");
        if (ret != NULL) {
            if(i % 2 == 0) {
                memcpy(thoigian_gui, &ret[6], 22);
                memcpy(tin, &ret_tin[9], 4);
                ret_tin = NULL;

            }
            else {
                memcpy(thoigian_den, &ret[6],22);
                memcpy(tinle, &ret_tin[9], 4);
                int error = memcmp(tin, tinle, 4);
                
                if (error == 0 ) {
                //Chuyen cac chuoi thoi gian gui va den thanh so
                memcpy(phut_gui, &thoigian_gui[13], 2);
                memcpy(phut_den, &thoigian_den[13], 2);
                memcpy(giay_gui, &thoigian_gui[16], 6);
                memcpy(giay_den, &thoigian_den[16], 6);
                //Tính thời gian delay của từng bản tin và cộng vào 1 delay cho tất cả bản tin
                diff = memcmp(phut_gui,phut_den,2);
                if (diff != 0) {
                    delay += (atof(phut_den) - atof(phut_gui))* 60000 + ((atof(giay_den) - atof(giay_gui))*1000);
                    count++;

                }
                else {
                    delay += (atof(giay_den) - atof(giay_gui))*1000;
                    count++;
                }
                }

            }  
            i++;  
        }
        token = strtok(NULL,"\n");
    }
    avg_delay = delay/count;
    printf("Do tre trung binh la: %.lf Millisecond\n", floor(avg_delay));

    fclose(fp);
    fp = NULL;
    return status;
}

