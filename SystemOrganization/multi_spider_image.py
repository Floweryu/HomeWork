# -*- coding:utf-8 -*-
# _author_='Zhang JunFeng'
# 此程序是多线程爬取图片的实例，采用了生产者和消费者模式。输入结果因网速的快慢而有差异。

import requests
from bs4 import BeautifulSoup
from urllib import request
import os
import time
import threading
# 对请求身份进行伪装
headers = {
            "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 "
                          "(KHTML, like Gecko) Chrome/70.0.3538.102 Safari/537.36"
        }

# 用来存储所有页面的 url 链接
PAGE_URLS = []
# 用来存储所有图片的 url 链接，作为生产者和消费者之间的缓冲池
IMG_URLS = []
gLock = threading.Lock()  # 给数据上锁，避免出现错误

# 生产者： 用来获取图片的url链接
# 消费者：从url链接中下载图片
# 全局变量：存储了表情包的链接


# 生产者函数：存储图片的 url 链接
def producer():
    while True:
        gLock.acquire()    # 对公共访问区域进行上锁
        if len(PAGE_URLS) == 0:
            gLock.release()     # 使用完成后释放
            break
        page_url = PAGE_URLS.pop()
        gLock.release()
        # 获取网页源代码
        response = requests.get(page_url, headers=headers)
        text = response.text
        # 解析源代码
        soup = BeautifulSoup(text, 'lxml')
        # atters 指寻找的条件
        img_list = soup.find_all("img", attrs={"class": "lazy image_dtb img-responsive"})

        for img in img_list:
            img_url = img['data-original']
            # 得到图片的 url 链接
            gLock.acquire()
            IMG_URLS.append(img_url)
            gLock.release()


def consumer():
    while True:
        gLock.acquire()
        if len(IMG_URLS) == 0 and len(PAGE_URLS) == 0:
            gLock.release()
            break
        if len(IMG_URLS) > 0:
            img_url = IMG_URLS.pop()
        else:
            img_url = ''
        gLock.release()

        if img_url:
            try:
                # 对网址进行分割取最后一个元素
                filename = img_url.split("/")[-1]
                # 创建图片的存储路径，'join' 拼接路径
                full_path = os.path.join("images", filename)
                # 下载图片
                request.urlretrieve(img_url, full_path)
                print("%s下载完成！！" % filename)
            except:
                print("=" * 30)
                print(img_url)
                print("=" * 30)


def main():
    start = time.time()
    # 1, 先获取所有页面的 url
    for x in range(1, 10):
        page_url = "https://www.doutula.com/article/list/?page=" + str(x)
        PAGE_URLS.append(page_url)
    # 十个生产者线程
    for x in range(10):
        th = threading.Thread(target=producer())
        th.start()
    # 十个消费者线程
    for x in range(10):
        th = threading.Thread(target=consumer())
        th.start()
    end = time.time()
    print(end - start)


if __name__ == '__main__':
    main()
