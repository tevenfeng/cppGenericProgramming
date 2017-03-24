url="https://api.thinkpage.cn/v3/weather/daily.json?key=agfpgwmnt8xiqvsb&location=tianjin&language=zh-Hans&unit=c&start=0&days=3"

items=$(echo curl $url)

$items | jq '.'