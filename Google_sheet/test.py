import gspread

sa = gspread.service_account(filename="A:\Code\Google_sheet\healthy-feat-390910-729c14c55127.json")
sh = sa.open("Dữ liệu rung Delta lần 5.1")

wks = sh.worksheet("2. Động cơ quay với vi bước 1/32 - ko lọc")

#print('Rows: ', wks.row_count)
#print('Cols: ', wks.col_count)

#print(wks.acell('A9').value)
#print(wks.cell(3, 4).value)

#print(wks.get_all_records())
#print(wks.get_all_values())

#wks.update('E3', 5)
#wks.update('D2:E3', [['Engineering', 'Tennis'], ['Business', 'Pottery']])
wks.update('L4803:O4805', [])

#for i in range (3, 5):
    #wks.update('E'+str(i)+':W'+str(i), [[2, 43, 47, 22, 83, 59, 33, 92, 66, 43, -127, 31, 2, 66, 41, 20, 76, 47, 26]])
#wks.update('F2', '=UPPER(E2)', raw=False)

#wks.delete_rows(25)