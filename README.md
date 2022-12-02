# 🚚 Cargos Delivery Simulator
> 💻 A Cpp Program That Was Designed To Simulate Event Of A Cargo Delivery Company Working According To A Time Schedule


> Note: The Following Description Is A Summerization Of The Project criteria if you want all details you can check the original documentation 
[Cargo Delivery](https://docs.google.com/document/d/1u9GVHDnvs0FZPNMREKbIfvw4MulcKC8I/edit)


## 💡 How The System Works ?
The Company Deals With Three Different Types Of Cargos And Trucks, They Are <b>Ordered By There Priority</b> :
- VIP 
- Special
- Normal </br>
-----------
The Goal Is To Deliver This Cargos To There Destination By According To Some Rules</br>

### ok But What Is This Rules ❓
It's Simple Check this out:-
1. Company Only Works From 5:00 To 23:00 Inclusive, if else Only Trucks Journeys and Metainance Are Only Allowed</br>

2. we check first if there a cargo needs to be immediately loaded <b>as it has excceeded it's waiting limits</b>

3.  Now We Start Loading The Remaining Cargos by the following :-      
    - We First Start Assigning VIP Cargos <b> Ordered By  There Priority Made Up Function </b> To Any Type Of The Trucks
    - Then Start Loading Special Cargos Only To Special Trucks if available
    - Check the normal trucks and assign it to either normal or vip trucks

>Note That No Truck Is Allowed To Start Moving Unless it's fully loaded or some of it's cargo got time limit
----
### Well, But What About The Events ❓
Here We Deal With 3 Types Of Events
1. Ready event : An Event Which Occurs When A New Cargo Is Added To My Storage
2. Cancellation event : An Event When The Customer Wants To Cancel The Cargo <b>Only Applicable If It's Still In Storage</b>  
3. Promotion event : An Event When The Customer Wants To Promote His Cargo To A Vip Cargo <b>Applicable only on Normal Cargos</b> 
-----
# Now and after we know what it's all about let's check how we can use the program ⬇️⬇️⬇️
Well it's quite simple don't worry just do as i say :D ...>
## Get Your Input File Ready
- All you need to do is to create your input file in the format shown in format.text in project Folder</br>
- Run The Program With User cpp Compiler <b>Visual Studio is recommended</b>

- Insert The File Number
- Choose One Of The Output Ways Shown Below :-

![](./images/Screenshot%20(153).png)
![](./images/Screenshot%20(151).png)
</br></br>
- output File Will Be In The Following Format

![](./images/Screenshot%20(155).png)


-----------------------

Hope You Find both the program and description useful :)