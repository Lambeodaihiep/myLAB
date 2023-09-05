import gspread

print("Dữ liệu rung Delta lần: ")
text = input()

sa = gspread.service_account(filename="A:\Code\Google_sheet\healthy-feat-390910-729c14c55127.json")

sh1 = sa.open("Dữ liệu rung Delta lần " + text + ".1")
sh2 = sa.open("Dữ liệu rung Delta lần " + text + ".2")
sh3 = sa.open("Dữ liệu rung Delta lần " + text + ".3")
sh4 = sa.open("Dữ liệu rung Delta lần " + text + ".4")
sh5 = sa.open("Dữ liệu rung Delta lần " + text + ".5")

wks = []

wks.append(sh1.worksheet("2. Động cơ quay với vi bước 1/32 - tín hiệu "))
wks.append(sh2.worksheet("2. Động cơ quay với vi bước 1/32 - tín hiệu "))
wks.append(sh3.worksheet("2. Động cơ quay với vi bước 1/32 - tín hiệu "))
wks.append(sh4.worksheet("2. Động cơ quay với vi bước 1/32 - tín hiệu "))
wks.append(sh5.worksheet("2. Động cơ quay với vi bước 1/32 - tín hiệu "))

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


data = wks[0].get('E3:W')

# Number of sample points
N = len(data)

for i in range(0, N):
    t.append(float(data[i][0]) / 5)

    x1.append(float(data[i][1]) / 5)
    y1.append(float(data[i][2]) / 5)
    z1.append(float(data[i][3]) / 5)

    x2.append(float(data[i][4]) / 5)
    y2.append(float(data[i][5]) / 5)
    z2.append(float(data[i][6]) / 5)

    x3.append(float(data[i][7]) / 5)
    y3.append(float(data[i][8]) / 5)
    z3.append(float(data[i][9]) / 5)

for i in range(1, 5):
    data = wks[i].get('E3:W')
    for j in range(0, N):
        t[j] = t[j] + float(data[j][0]) / 5

        x1[j] = x1[j] + float(data[j][1]) / 5
        y1[j] = y1[j] + float(data[j][2]) / 5
        z1[j] = z1[j] + float(data[j][3]) / 5

        x2[j] = x2[j] + float(data[j][4]) / 5
        y2[j] = y2[j] + float(data[j][5]) / 5
        z2[j] = z2[j] + float(data[j][6]) / 5

        x3[j] = x3[j] + float(data[j][7]) / 5
        y3[j] = y3[j] + float(data[j][8]) / 5
        z3[j] = z3[j] + float(data[j][9]) / 5

listdataUpload = list()

for i in range(0, N):
    dataUpload = list()

    dataUpload.append(t[i])

    dataUpload.append(x1[i])
    dataUpload.append(y1[i])
    dataUpload.append(z1[i])

    dataUpload.append(x2[i])
    dataUpload.append(y2[i])
    dataUpload.append(z2[i])

    dataUpload.append(x3[i])
    dataUpload.append(y3[i])
    dataUpload.append(x3[i])

    listdataUpload.append(dataUpload)

sh = sa.open("Dữ liệu rung Delta trung bình lần " + text) # tên sheet muốn sử dụng, đổi mỗi lần đọc được dữ liệu mới

wks_mean = sh.worksheet("2. Động cơ quay với vi bước 1/32 - tín hiệu ") # tên worksheet muốn sử dụng, cái này mặc định rồi đừng có mà đổi

# Đẩy dữ liệu lên gg sheet
wks_mean.update('E3:W', listdataUpload)
print("done")


