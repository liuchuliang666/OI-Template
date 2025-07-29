import datetime
from datetime import timezone, timedelta
import os

# 创建北京时区（UTC+8）
beijing_tz = timezone(timedelta(hours=8))

# 获取北京当前日期和时间
current_time = datetime.datetime.now(beijing_tz).strftime("%Y-%m-%d %H:%M:%S")

# 执行 Git 操作
os.system(f'git add .')  # 添加文件到暂存区
os.system(f'git commit --allow-empty -m "update at {current_time}"')  # 提交到本地仓库
os.system('git push origin main')  # 推送到远程 main 分支

print(f"已提交到Git仓库（{current_time}）。")