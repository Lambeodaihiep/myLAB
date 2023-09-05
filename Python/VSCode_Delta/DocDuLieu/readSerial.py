import time

import serial
import gspread

print("Dữ liệu rung Delta lần: ")
text = input()

# thao tác với file txt trước rồi mới thao tác với google sheet
wf = open("A:\Code\Python\VSCode_Delta\DocDuLieu\OUTPUT_Serial.txt", "w")

sa = gspread.service_account(filename="A:\Code\Google_sheet\healthy-feat-390910-729c14c55127.json")
sh = sa.open("Dữ liệu rung Delta lần " + text) # tên sheet muốn sử dụng, đổi mỗi lần đọc được dữ liệu mới

wks = sh.worksheet("2. Động cơ quay với vi bước 1/32 - tín hiệu ") # tên worksheet muốn sử dụng, cái này mặc định rồi đừng có mà đổi

# Khởi tạo đối tượng Serial với baudrate và cổng COM tương ứng
ser = serial.Serial("COM5", 2000000)

# Xóa hết dữ liệu còn lại trong serial
ser.flushInput()
ser.flushOutput()

# Đóng port serial
ser.close()

# Mở lại port serial để bắt đầu dữ liệu mới
ser.open()

count = 0
numMau = 4800 + 22

valMin = [0, 364, 37, 43, 35, 37, 29, 37, 44, 35, 368, 36, 43, 35, 37, 28, 36, 43, 35]
# valMin = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
valGndx = 75
valGndy = 50
valGndz = 25
valGnd = [
    0,
    valGndx,
    valGndy,
    valGndz,
    valGndx,
    valGndy,
    valGndz,
    valGndx,
    valGndy,
    valGndz,
    valGndx,
    valGndy,
    valGndz,
    valGndx,
    valGndy,
    valGndz,
    valGndx,
    valGndy,
    valGndz,
]

valCalib1 = 0
valCalib2 = 10
valCalib3 = 20
valCalib = [
    0,
    valCalib1,
    valCalib1,
    valCalib1,
    valCalib2,
    valCalib2,
    valCalib2,
    valCalib3,
    valCalib3,
    valCalib3,
    valCalib1,
    valCalib1,
    valCalib1,
    valCalib2,
    valCalib2,
    valCalib2,
    valCalib3,
    valCalib3,
    valCalib3,
]

listdataUpload = list()

while True:
    data = ser.readline().decode().strip()

    # In giá trị serial ra màn hình
    listData = list(data.split(","))
    data = ""
    dataUpload = list() # dữ liệu đẩy lên google sheet

    for i in range(0, len(listData) - 1):
        dataUpload.append(int(listData[i]) - valMin[i] + valGnd[i] + valCalib[i])
        data = data + str(int(listData[i]) - valMin[i] + valGnd[i] + valCalib[i]) + "\t"

    wf.write(data + "\n")

    # print(data+'\n')

    listdataUpload.append(dataUpload)

    if count >= numMau:
        break
    else:
        count += 1
        print(count)

# Đẩy dữ liệu lên gg sheet
wks.update('E3:W', listdataUpload)
print("done")
# Đóng kết nối serial khi không sử dụng nữa
ser.close()
