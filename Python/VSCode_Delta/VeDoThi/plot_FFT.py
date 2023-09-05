import matplotlib.pyplot as plt
import gspread

print("Bạn muốn update cho bảng thành phần hay bảng trung bình:")
print("1 - Thành phần")
print("2 - Trung bình")
choice = int(input())

sa = gspread.service_account(filename="A:\Code\Google_sheet\healthy-feat-390910-729c14c55127.json")

if choice == 1:
    print("Dữ liệu rung Delta lần: ")
    text = input()
    sh = sa.open("Dữ liệu rung Delta lần " + text) # tên sheet muốn sử dụng, đổi mỗi lần muốn đọc dữ liệu ở sheet khác
elif choice == 2:
    print("Dữ liệu rung Delta lần: ")
    text = input()
    sh = sa.open("Dữ liệu rung Delta trung bình lần " + text)

# print("Dữ liệu rung Delta lần: ")
# text = input()

# sa = gspread.service_account(filename="A:\Code\Google_sheet\healthy-feat-390910-729c14c55127.json")
# sh = sa.open("Dữ liệu rung Delta lần " + text) # tên sheet muốn sử dụng, đổi mỗi lần muốn đọc dữ liệu ở sheet khác

wks = sh.worksheet("2. Động cơ quay với vi bước 1/32 - ko lọc") # tên worksheet muốn sử dụng, cái này mặc định rồi đừng có mà đổi
#wks = sh.worksheet("2. Động cơ quay với vi bước 1/32 - có lọc") # tên worksheet muốn sử dụng, cái này mặc định rồi đừng có mà đổi

data = wks.get('L3:U')

# print(read)
# del read[0:0]

t = []

x1 = []
y1 = []
z1 = []

x2 = []
y2 = []
z2 = []

x3 = []
y3 = []
z3 = []

# Number of sample points
N = len(data)

for i in range(0, len(data)):
    t.append(float(data[i][0]))

    x1.append(float(data[i][1]))
    y1.append(float(data[i][2]))
    z1.append(float(data[i][3]))

    x2.append(float(data[i][4]))
    y2.append(float(data[i][5]))
    z2.append(float(data[i][6]))

    x3.append(float(data[i][7]))
    y3.append(float(data[i][8]))
    z3.append(float(data[i][9]))

plt.figure(figsize=(16, 9), dpi=90)

linewidth = 2
linewidth1 = 2

# plt.subplot(2, 1, 2)
# plt.plot(f[2:], x_A[2:], f[2:], y_A[2:], f[2:], z_A[2:])
# plt.plot(t, x1, label="x_1", color="blue", linewidth=linewidth, linestyle="dashed")
# plt.plot(t, y1, label="y_1", color="red", linewidth=linewidth, linestyle="dashed")
# plt.plot(t, z1, label="z_1", color="#00aa00ff", linewidth=linewidth, linestyle="dashed")

# plt.plot(t, x2, label="x_2", color="blue", linewidth=linewidth1, linestyle="dashdot")
# plt.plot(t, y2, label="y_2", color="red", linewidth=linewidth1, linestyle="dashdot")
# plt.plot(t, z2, label="z_2", color="#00aa00ff", linewidth=linewidth1, linestyle="dashdot")

#plt.plot(t, x3, label="x_3", color="blue", linewidth=linewidth1, linestyle="solid")
#plt.plot(t, y3, label="y_3", color="red", linewidth=linewidth1, linestyle="solid")
plt.plot(t, z3, label="z_3", color="#00aa00ff", linewidth=linewidth1, linestyle="solid")

fontsize = 28

plt.title("Kết quả biến đổi Fourier tín hiệu trục Z cảm biến số 3 khi m = 20g", fontsize=fontsize, weight="bold")
plt.ylabel("Biên độ (Analog)", fontsize=fontsize, weight="bold")
plt.xlabel("Tần số (Hz)", fontsize=fontsize, weight="bold")

# plt.title("Tín hiệu", fontsize=fontsize, weight="bold")
# plt.ylabel("Giá trị (Analog)", fontsize=fontsize, weight="bold")
# plt.xlabel("Thời gian (s)", fontsize=fontsize, weight="bold")

plt.subplots_adjust(
    top=0.937, bottom=0.125, left=0.082, right=0.975, hspace=0.203, wspace=0.2
)

# Giá trị tối đa và tối thiểu trên trục x và trục y
x_min = 0
x_max = 12
y_min = 0
y_max = 2
plt.xlim(x_min, x_max)
plt.ylim(y_min, y_max)

plt.xticks(fontsize=fontsize)
plt.yticks(fontsize=fontsize)

plt.legend(fontsize=fontsize, loc="upper right")
plt.grid()

# Chọn 3 điểm trên đồ thị
points = plt.ginput(9)

# In ra tọa độ của các điểm đã chọn
print("Tọa độ của các điểm đã chọn:")
for point in points:
    pointX = point[0]
    pointY = point[1]
    print("Tọa độ của điểm đã chọn: ({}, {})".format(pointX, pointY))
    plt.text(pointX, pointY, "({}, {})".format(round(pointX, 3), round(pointY, 3)), rotation = 30, rotation_mode = 'anchor', fontsize=fontsize-10, ha='left', va='bottom')
    plt.plot(pointX, pointY, marker="o", color="#ffaaffff", linewidth=20)


# xx3 = x3
# yy3 = y3
# zz3 = z3

# pointX3 = []
# pointY3 = []
# pointZ3 = []

# for i in range(0, 50):
#     if t[zz3.index(max(zz3))] < 10:
#         pointZ3.append([max(zz3), t[zz3.index(max(zz3))]])
#     t.remove(t[zz3.index(max(zz3))])
#     zz3.remove(max(zz3))
#     if(len(pointZ3) > 2):
#         break

# for i in range(0, 50):
#     if t[yy3.index(max(yy3))] < 10:
#         pointY3.append([max(yy3), t[yy3.index(max(yy3))]])
#     t.remove(t[yy3.index(max(yy3))])
#     yy3.remove(max(yy3))
#     if(len(pointY3) > 2):
#         break

# for i in range(0, 50):
#     if t[xx3.index(max(xx3))] < 10:
#         pointX3.append([max(xx3), t[xx3.index(max(xx3))]])
#     t.remove(t[xx3.index(max(xx3))])
#     xx3.remove(max(xx3))
#     if(len(pointX3) > 2):
#         break

# # # In ra tọa độ của các điểm đã chọn
# print("Tọa độ của các điểm đã chọn:")
# for point1 in pointZ3:
#     pointX = point1[1]
#     pointY = point1[0]
#     print("Tọa độ của điểm đã chọn: ({}, {})".format(pointX, pointY))
#     plt.text(pointX, pointY, "({}, {})".format(round(pointX, 3), round(pointY, 3)), fontsize=fontsize-10, ha='left', va='bottom')
#     plt.plot(pointX, pointY, marker="o", color="#ffaaffff", linewidth=20)

# for point2 in pointY3:
#     pointX = point2[1]
#     pointY = point2[0]
#     print("Tọa độ của điểm đã chọn: ({}, {})".format(pointX, pointY))
#     plt.text(pointX, pointY, "({}, {})".format(round(pointX, 3), round(pointY, 3)), fontsize=fontsize-10, ha='left', va='bottom')
#     plt.plot(pointX, pointY, marker="o", color="#ffaaffff", linewidth=20)

# for point2 in pointX3:
#     pointX = point2[1]
#     pointY = point2[0]
#     print("Tọa độ của điểm đã chọn: ({}, {})".format(pointX, pointY))
#     plt.text(pointX, pointY, "({}, {})".format(round(pointX, 3), round(pointY, 3)), fontsize=fontsize-10, ha='left', va='bottom')
#     plt.plot(pointX, pointY, marker="o", color="#ffaaffff", linewidth=20)

# plt.plot([pointX,pointX],[0,pointY], linestyle='--', color='gray', linewidth=1)
# plt.plot([0,pointX], [pointY,pointY], linestyle='--', color='gray', linewidth=1)


plt.show()