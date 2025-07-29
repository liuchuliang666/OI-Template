import datetime
from datetime import timezone, timedelta
import os

# 创建北京时区（UTC+8）
beijing_tz = timezone(timedelta(hours=8))

# 获取北京当前日期和时间
current_time = datetime.datetime.now(beijing_tz).strftime("%Y-%m-%d %H:%M:%S")

# 确保docs目录存在
os.makedirs("docs", exist_ok=True)

# 将日期和时间写入docs/timeidx文件
with open("docs/timeidx", "w") as file:
    file.write(current_time)
