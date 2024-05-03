Các bước setup cho Project đồng hồ báo thức:
-	Ấn button reset để init các module clock, softimer, LUART, LSPI, button, led.
-	Sau khi ấn reset màn hình led MAX7219 hiển thị 00-00-00 (giá trị ban đầu của hh, mm, ss).
-	Từ Hercules gởi frame theo format (shh-mm-ss) để set thời gian bắt đầu cho đồng hồ. 
VD: s12-34-56
(Nếu gởi sai frame như s25-60-60 (hh>=24 || mm>=60 || ss>=60) thì báo lỗi bằng cách hiển thị ra led --------)
Nếu set thời gian bắt đầu thành công thì đồng hồ sẽ hiển thị ra thời gian mình set, rồi count up.
-	Gởi tiếp frame tiếp theo theo format (ahh-mm-ss) để set thời gian báo thức.
-	Đến thời gian báo thức, led red blue green sáng luân phiên nhau.
Chỉnh giờ cho đồng hồ:
Button 1: Chỉnh giờ
Button 2: Chỉnh phút
	Phải set giờ bắt đầu bằng cách gởi frame (shh-mm-ss) thì mới chỉnh giờ được.
