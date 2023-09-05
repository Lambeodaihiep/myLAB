import matplotlib.pyplot as plt
import numpy as np
from scipy.fft import fft, fftfreq, fftshift
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

wks = sh.worksheet("2. Động cơ quay với vi bước 1/32 - ko lọc") # tên worksheet muốn sử dụng, cái này mặc định rồi đừng có mà đổi
#wks = sh.worksheet("2. Động cơ quay với vi bước 1/32 - có lọc") # tên worksheet muốn sử dụng, cái này mặc định rồi đừng có mà đổi

data = wks.get('A3:J')

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

# sample spacing
millis = (t[N - 1] - t[0]) / (N - 1)

scaleTimes = 1000

Fs = 1 / (millis / scaleTimes)
Ts = 1.0 / Fs

print("Số mẫu: " + str(N))
print("Khoảng cách lấy mẫu: " + str(millis))
print("Tần số lấy mẫu: " + str(Fs))


plt.subplot(2, 1, 1)
plt.plot(t, x1, t, y1, t, z1, t, x2, t, y2, t, z2, t, x3, t, y3, t, z3)
plt.title("Tín hiệu rung")
plt.ylabel("Giá trị analog")
plt.xlabel("Thời gian (ms)")

# fft_data1 = np.array(data1, dtype=np.float32)

tf = fftfreq(N, Ts)
tplot = fftshift(tf)

x1f = fft(x1)
x1plot = fftshift(x1f)
y1f = fft(y1)
y1plot = fftshift(y1f)
z1f = fft(z1)
z1plot = fftshift(z1f)

x2f = fft(x2)
x2plot = fftshift(x2f)
y2f = fft(y2)
y2plot = fftshift(y2f)
z2f = fft(z2)
z2plot = fftshift(z2f)

x3f = fft(x3)
x3plot = fftshift(x3f)
y3f = fft(y3)
y3plot = fftshift(y3f)
z3f = fft(z3)
z3plot = fftshift(z3f)


plt.subplot(2, 1, 2)
plt.plot(tplot[N // 2 + 1 : N], 2.0 / N * np.abs(x1plot[N // 2 + 1 : N]))
plt.title("FFT")
plt.ylabel("Biên độ")
plt.xlabel("Tần số (Hz)")

listdataUpload = list()

index = N // 2 + 1
for i in range(index, N):
    dataUpload = list()

    dataUpload.append(tplot[i])

    dataUpload.append(2.0 / N * np.abs(x1plot[i]))
    dataUpload.append(2.0 / N * np.abs(y1plot[i]))
    dataUpload.append(2.0 / N * np.abs(z1plot[i]))

    dataUpload.append(2.0 / N * np.abs(x2plot[i]))
    dataUpload.append(2.0 / N * np.abs(y2plot[i]))
    dataUpload.append(2.0 / N * np.abs(z2plot[i]))

    dataUpload.append(2.0 / N * np.abs(x3plot[i]))
    dataUpload.append(2.0 / N * np.abs(y3plot[i]))
    dataUpload.append(2.0 / N * np.abs(z3plot[i]))

    listdataUpload.append(dataUpload)

wks.update('L3:U', listdataUpload)

# plt.subplots_adjust(top=0.961,bottom=0.06,left=0.053,right=0.992,hspace=0.203,wspace=0.2)
# plt.grid()
# plt.show()
