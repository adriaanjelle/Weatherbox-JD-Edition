[Variables]
WeatherAPIKey=71f92ea9dd2f4790b92ea9dd2f779061

WeatherUnitsMetric=m
WeatherUnitsImperial=e

WeatherRegExpString=((?(?=null)null|".*"))
WeatherRegExpNumber=((?(?=null)null|.*))
WeatherRegExpStringDaily15=\[((?(?=null)null|".*")),((?(?=null)null|".*")),((?(?=null)null|".*")),((?(?=null)null|".*")),((?(?=null)null|".*")),((?(?=null)null|".*")),((?(?=null)null|".*")),((?(?=null)null|".*")),((?(?=null)null|".*")),((?(?=null)null|".*")),((?(?=null)null|".*")),((?(?=null)null|".*")),((?(?=null)null|".*")),((?(?=null)null|".*")),((?(?=null)null|".*"))\]
WeatherRegExpNumberDaily15=\[((?(?=null)null|.*)),((?(?=null)null|.*)),((?(?=null)null|.*)),((?(?=null)null|.*)),((?(?=null)null|.*)),((?(?=null)null|.*)),((?(?=null)null|.*)),((?(?=null)null|.*)),((?(?=null)null|.*)),((?(?=null)null|.*)),((?(?=null)null|.*)),((?(?=null)null|.*)),((?(?=null)null|.*)),((?(?=null)null|.*)),((?(?=null)null|.*))\]
WeatherRegExpStringDaily30=\[((?(?=null)null|".*")),((?(?=null)null|".*")),((?(?=null)null|".*")),((?(?=null)null|".*")),((?(?=null)null|".*")),((?(?=null)null|".*")),((?(?=null)null|".*")),((?(?=null)null|".*")),((?(?=null)null|".*")),((?(?=null)null|".*")),((?(?=null)null|".*")),((?(?=null)null|".*")),((?(?=null)null|".*")),((?(?=null)null|".*")),((?(?=null)null|".*")),((?(?=null)null|".*")),((?(?=null)null|".*")),((?(?=null)null|".*")),((?(?=null)null|".*")),((?(?=null)null|".*")),((?(?=null)null|".*")),((?(?=null)null|".*")),((?(?=null)null|".*")),((?(?=null)null|".*")),((?(?=null)null|".*")),((?(?=null)null|".*")),((?(?=null)null|".*")),((?(?=null)null|".*")),((?(?=null)null|".*")),((?(?=null)null|".*"))\]
WeatherRegExpNumberDaily30=\[((?(?=null)null|.*)),((?(?=null)null|.*)),((?(?=null)null|.*)),((?(?=null)null|.*)),((?(?=null)null|.*)),((?(?=null)null|.*)),((?(?=null)null|.*)),((?(?=null)null|.*)),((?(?=null)null|.*)),((?(?=null)null|.*)),((?(?=null)null|.*)),((?(?=null)null|.*)),((?(?=null)null|.*)),((?(?=null)null|.*)),((?(?=null)null|.*)),((?(?=null)null|.*)),((?(?=null)null|.*)),((?(?=null)null|.*)),((?(?=null)null|.*)),((?(?=null)null|.*)),((?(?=null)null|.*)),((?(?=null)null|.*)),((?(?=null)null|.*)),((?(?=null)null|.*)),((?(?=null)null|.*)),((?(?=null)null|.*)),((?(?=null)null|.*)),((?(?=null)null|.*)),((?(?=null)null|.*)),((?(?=null)null|.*))\]

WeatherSubstitute="^null$":"", '^"(.*)"$':"\1", "^\\1$":""
WeatherSubstituteIcons="^0$":"storm", "^1$":"storm", "^2$":"storm", "^3$":"storm", "^4$":"storm", "^5$":"sleet", "^6$":"sleet", "^7$":"sleet", "^8$":"sleet", "^9$":"rain", "^10$":"sleet", "^11$":"rain", "^12$":"rain", "^13$":"snow", "^14$":"snow", "^15$":"snow", "^16$":"snow", "^17$":"sleet", "^18$":"sleet", "^19$":"fog", "^20$":"fog", "^21$":"fog", "^22$":"fog", "^23$":"windy", "^24$":"windy", "^25$":"snow", "^26$":"cloudy", "^27$":"cloudy-night", "^28$":"cloudy-day", "^29$":"cloudy-night", "^30$":"cloudy-day", "^31$":"clear-night", "^32$":"clear-day", "^33$":"partly-cloudy-night", "^34$":"partly-cloudy-day", "^35$":"sleet", "^36$":"clear-day", "^37$":"storm-day", "^38$":"storm-day", "^39$":"rain", "^40$":"rain", "^41$":"snow-day", "^42$":"snow", "^43$":"snow", "^44$":"unknown", "^45$":"rain-night", "^46$":"snow-night", "^47$":"storm-night", "^na$":"", "":"unknown"

WeatherSubstituteMoonPhaseIcons="^N$":"new-moon", "^WXC$":"waxing-crescent", "^FQ$":"first-quarter", "^WXG$":"waxing-gibbous", "^F$":"full-moon", "^WNG$":"waning-gibbous", "^LQ$":"third-quarter", "^WNC$":"waning-crescent", "^$":"unknown"

TimeFormat24HTime0=%#I:%M %p
TimeFormat24HTime1=%H:%M

; ================================================

[mInternetConnectivity]
Measure=Plugin
Plugin=SysInfo

SysInfoType=INTERNET_CONNECTIVITY

OnChangeAction=[!UpdateMeasure mWeatherCheckIfLocationChanged]

; ================================================

[mWeatherCheckIfLocationChanged]
Measure=String

String=#WeatherLocation#

IfMatchMode=1
IfMatch=^#CachedWeatherLocationVariable#$
IfMatchAction=[!Log "Location has not changed, skipping Nominatim. Location: #CachedWeatherLocation#." Notice] [!WriteKeyValue Variables CachedWeatherLocationVariable "#WeatherLocation#" "#@#WeatherParserCache.inc"] [!EnableMeasure mWeatherParent] [!UpdateMeasure mWeatherParent]
IfNotMatchAction=[!Log "Location has changed, fetching new location with Nominatim." Notice] [!WriteKeyValue Variables CachedWeatherLocationVariable "#WeatherLocation#" "#@#WeatherParserCache.inc"] [!EnableMeasure mWeatherLocationParent] [!UpdateMeasure mWeatherLocationParent]

UpdateDivider=-1

; ================================================

[mWeatherLocationParent]
Measure=WebParser

URL=https://nominatim.openstreetmap.org/search?q=#WeatherLocation#&format=geocodejson&limit=1&addressdetails=1
RegExp=(?siU)"features":\[{"type":"Feature","properties":{"geocoding":{.*,"label":"(.*)",.*,"admin":{"level\d+":"(.*)".*}}},"geometry":{"type": "Point","coordinates": \[(.*), (.*)\]}}\]
UserAgent=Rainmeter: #RootConfig# by Jelle Dekkers (github.com/adriaanjelle)
UpdateRate=1

FinishAction=[!UpdateMeasureGroup WeatherLocation] [!EnableMeasure mWeatherParent] [!UpdateMeasure mWeatherParent] [!Log "Location found: [mWeatherLocation]." Notice] [!WriteKeyValue Variables CachedWeatherLocation "[mWeatherLocation]" "#@#WeatherParserCache.inc"] [!WriteKeyValue Variables CachedWeatherLocationCity "[mWeatherLocationCity]" "#@#WeatherParserCache.inc"] [!WriteKeyValue Variables CachedWeatherLocationLat "[mWeatherLocationLat]" "#@#WeatherParserCache.inc"] [!WriteKeyValue Variables CachedWeatherLocationLon "[mWeatherLocationLon]" "#@#WeatherParserCache.inc"]
OnConnectErrorAction=[!UpdateMeasureGroup WeatherLocation] [!EnableMeasure mWeatherParent] [!UpdateMeasure mWeatherParent] [!Log "Unable to connect to Nominatim." Error]
OnRegExpErrorAction=[!UpdateMeasureGroup WeatherLocation] [!EnableMeasure mWeatherParent] [!UpdateMeasure mWeatherParent] [!Log "No results found for that location." Error]

Disabled=1
UpdateDivider=-1

; ================================================

[mWeatherLocation]
Group=WeatherLocation
Measure=WebParser

URL=[mWeatherLocationParent]
StringIndex=1

Substitute="":"#CachedWeatherLocation#"

[mWeatherLocationCity]
Group=WeatherLocation
Measure=WebParser

URL=[mWeatherLocationParent]
StringIndex=2

Substitute="":"#CachedWeatherLocationCity#"

[mWeatherLocationLat]
Group=WeatherLocation
Measure=WebParser

URL=[mWeatherLocationParent]
StringIndex=4

Substitute="":"#CachedWeatherLocationLat#"

[mWeatherLocationLon]
Group=WeatherLocation
Measure=WebParser

URL=[mWeatherLocationParent]
StringIndex=3

Substitute="":"#CachedWeatherLocationLon#"

; ================================================

[mSystemLocale]
Measure=Registry

RegHKey=HKEY_CURRENT_USER
RegKey=Control Panel\International
RegValue=LocaleName

RegExpSubstitute=1
Substitute="^$":"en-US", "^0$":"en-US"

UpdateDivider=-1

; ================================================

[mWeatherParent]
Group=Parent
Measure=WebParser

URL=https://api.weather.com/v3/aggcommon/v3-wx-observations-current;v3-wx-forecast-daily-15day?format=json&geocode=[&mWeatherLocationLat],[&mWeatherLocationLon]&units=[#WeatherUnits[#WeatherUnits]]&language=[#Language]&apiKey=#WeatherAPIKey#
RegExp=(?siU)"v3-wx-observations-current":.*{(.*)}.*"v3-wx-forecast-daily-15day":.*{(.*),"daypart":\[{(.*)}\]}
UserAgent=Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/86.0.4240.111 Safari/537.36
UpdateRate=(15*60)

FinishAction=[!EnableMeasureGroup Weather] [!UpdateMeasureGroup Weather] [!UpdateMeter *] [!UpdateMeter *] [!Redraw] [!Log "Finished parsing weather data." Notice]
OnConnectErrorAction=[!EnableMeasureGroup Weather] [!UpdateMeasureGroup Weather] [!UpdateMeter *] [!UpdateMeter *] [!Redraw] [!Log "Unable to connect to Weather.com." Error]
OnRegExpErrorAction=[!EnableMeasureGroup Weather] [!UpdateMeasureGroup Weather] [!UpdateMeter *] [!UpdateMeter *] [!Redraw] [!Log "Something went wrong." Error]

DynamicVariables=1
Disabled=1

; ================================================

[mWeatherUnitsTemperature]
Measure=String

String=[#WeatherUnits[#WeatherUnits]]

RegExpSubstitute=1
Substitute="^m$":"C", "^e$":"F"

UpdateDivider=-1

[mWeatherUnitsSpeed]
Measure=String

String=[#WeatherUnits[#WeatherUnits]]

RegExpSubstitute=1
Substitute="^m$":"km/h", "^e$":"mi/h"

UpdateDivider=-1

[mWeatherUnitsDistance]
Measure=String

String=[#WeatherUnits[#WeatherUnits]]

RegExpSubstitute=1
Substitute="^m$":"km", "^e$":"mi"

UpdateDivider=-1

[mWeatherUnitsPressure]
Measure=String

String=[#WeatherUnits[#WeatherUnits]]

RegExpSubstitute=1
Substitute="^m$":"mb", "^e$":"in"

UpdateDivider=-1

; ================================================

[mWeatherCurrentTemperature]
Group=Weather
Measure=WebParser

URL=[mWeatherParent]
StringIndex=1
RegExp=(?siU)"temperature":#WeatherRegExpNumber#[,}\]]
StringIndex2=1

RegExpSubstitute=1
Substitute="#WeatherSubstitute#", "^$":"--"

[mWeatherCurrentTemperatureFeelsLike]
Group=Weather
Measure=WebParser

URL=[mWeatherParent]
StringIndex=1
RegExp=(?siU)"temperatureFeelsLike":#WeatherRegExpNumber#[,}\]]
StringIndex2=1

RegExpSubstitute=1
Substitute="#WeatherSubstitute#", "^$":"--"

[mWeatherCurrentIcon]
Group=Weather
Measure=WebParser

URL=[mWeatherParent]
StringIndex=1
RegExp=(?siU)"iconCode":#WeatherRegExpNumber#[,}\]]
StringIndex2=1

RegExpSubstitute=1
Substitute="#WeatherSubstitute#", "#WeatherSubstituteIcons#"

[mWeatherCurrentPhrase]
Group=Weather
Measure=WebParser

URL=[mWeatherParent]
StringIndex=1
RegExp=(?siU)"wxPhraseLong":#WeatherRegExpString#[,}\]]
StringIndex2=1

RegExpSubstitute=1
Substitute="#WeatherSubstitute#", "^$":"N/A"

[mWeatherCurrentPrecip1H]
Group=Weather
Measure=WebParser

URL=[mWeatherParent]
StringIndex=1
RegExp=(?siU)"precip1Hour":#WeatherRegExpNumber#[,}\]]
StringIndex2=1

RegExpSubstitute=1
Substitute="#WeatherSubstitute#", "^$":"--"

[mWeatherCurrentPrecip6H]
Group=Weather
Measure=WebParser

URL=[mWeatherParent]
StringIndex=1
RegExp=(?siU)"precip6Hour":#WeatherRegExpNumber#[,}\]]
StringIndex2=1

RegExpSubstitute=1
Substitute="#WeatherSubstitute#", "^$":"--"

[mWeatherCurrentPrecip24H]
Group=Weather
Measure=WebParser

URL=[mWeatherParent]
StringIndex=1
RegExp=(?siU)"precip24Hour":#WeatherRegExpNumber#[,}\]]
StringIndex2=1

RegExpSubstitute=1
Substitute="#WeatherSubstitute#", "^$":"--"

[mWeatherCurrentPressure]
Group=Weather
Measure=WebParser

URL=[mWeatherParent]
StringIndex=1
RegExp=(?siU)"pressureAltimeter":#WeatherRegExpNumber#[,}\]]
StringIndex2=1

RegExpSubstitute=1
Substitute="#WeatherSubstitute#", "^$":"--"

[mWeatherCurrentHumidity]
Group=Weather
Measure=WebParser

URL=[mWeatherParent]
StringIndex=1
RegExp=(?siU)"relativeHumidity":#WeatherRegExpNumber#[,}\]]
StringIndex2=1

RegExpSubstitute=1
Substitute="#WeatherSubstitute#", "^$":"--"

[mWeatherCurrentUVDescription]
Group=Weather
Measure=WebParser

URL=[mWeatherParent]
StringIndex=1
RegExp=(?siU)"uvDescription":#WeatherRegExpString#[,}\]]
StringIndex2=1

RegExpSubstitute=1
Substitute="#WeatherSubstitute#", "^$":"N/A"

[mWeatherCurrentUVIndex]
Group=Weather
Measure=WebParser

URL=[mWeatherParent]
StringIndex=1
RegExp=(?siU)"uvIndex":#WeatherRegExpNumber#[,}\]]
StringIndex2=1

RegExpSubstitute=1
Substitute="#WeatherSubstitute#", "^$":"--"

[mWeatherCurrentVisibilityRAW]
Group=Weather
Measure=WebParser

URL=[mWeatherParent]
StringIndex=1
RegExp=(?siU)"visibility":#WeatherRegExpNumber#[,}\]]
StringIndex2=1

RegExpSubstitute=1
Substitute="#WeatherSubstitute#"

[mWeatherCurrentVisibility]
Group=Weather
Measure=String

String=[mWeatherCurrentVisibilityRAW] [mWeatherUnitsDistance]

RegExpSubstitute=1
Substitute="10 mi":"∞", "16.09 km":"∞"

DynamicVariables=1
Disabled=1
UpdateDivider=-1

[mWeatherCurrentWindDirection]
Group=Weather
Measure=WebParser

URL=[mWeatherParent]
StringIndex=1
RegExp=(?siU)"windDirection":#WeatherRegExpNumber#[,}\]]
StringIndex2=1

RegExpSubstitute=1
Substitute="#WeatherSubstitute#", "^$":"0"

[mWeatherCurrentWindDirectionIcon]
Group=Weather
Measure=Calc

Formula=(Round([mWeatherCurrentWindDirection]/15)*15)%360

RegExpSubstitute=1
Substitute="^(.*)$":"from-\1"

DynamicVariables=1
Disabled=1
UpdateDivider=-1

[mWeatherCurrentWindDirectionCardinal]
Group=Weather
Measure=WebParser

URL=[mWeatherParent]
StringIndex=1
RegExp=(?siU)"windDirectionCardinal":#WeatherRegExpString#[,}\]]
StringIndex2=1

RegExpSubstitute=1
Substitute="#WeatherSubstitute#", "^$":"--"

[mWeatherCurrentWindSpeed]
Group=Weather
Measure=WebParser

URL=[mWeatherParent]
StringIndex=1
RegExp=(?siU)"windSpeed":#WeatherRegExpNumber#[,}\]]
StringIndex2=1

RegExpSubstitute=1
Substitute="#WeatherSubstitute#", "^$":"--"
