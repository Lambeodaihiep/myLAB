
import gspread

sa = gspread.service_account(filename="A:\Code\Google_sheet\healthy-feat-390910-729c14c55127.json")

# print("Dữ liệu rung Delta lần: ")
# text = input()
sh1 = sa.open("Dữ liệu rung Delta lần 26.5") # tên sheet muốn sử dụng, đổi mỗi lần muốn đọc dữ liệu ở sheet khác

wks1 = sh1.worksheet("2. Động cơ quay với vi bước 1/32 - ko lọc") # tên worksheet muốn sử dụng, cái này mặc định rồi đừng có mà đổi
#wks = sh.worksheet("2. Động cơ quay với vi bước 1/32 - có lọc") # tên worksheet muốn sử dụng, cái này mặc định rồi đừng có mà đổi

data = wks1.get('A888:J1863')

sh2 = sa.open("copy dữ liệu hình chữ nhật")

wks2 = sh2.worksheet("10g")

wks2.update('A2:J', data)

# plt.subplots_adjust(top=0.961,bottom=0.06,left=0.053,right=0.992,hspace=0.203,wspace=0.2)
# plt.grid()
# plt.show()
