   M S B A M L   `   `   `  ���� C  ?WpfApp17, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null#clr-namespace:WpfApp17WpfApp17  U QLiveCharts.Wpf, Version=0.9.7.0, Culture=neutral, PublicKeyToken=0bc1f845d1ebb8dfG4clr-namespace:LiveCharts.Wpf;assembly=LiveCharts.WpfLiveCharts.Wpf     WpfApp17.MainWindow   \ XPresentationFramework, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35e aSystem.Windows.Controls.Ribbon, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089W SPresentationCore, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35R NWindowsBase, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35F 9http://schemas.microsoft.com/winfx/2006/xaml/presentation     R NSystem.Xaml, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089:x,http://schemas.microsoft.com/winfx/2006/xaml     @d2http://schemas.microsoft.com/expression/blend/2008     Jmc;http://schemas.openxmlformats.org/markup-compatibility/2006     (localclr-namespace:WpfApp17     Dlvc4clr-namespace:LiveCharts.Wpf;assembly=LiveCharts.Wpf     -     � Title$0  *Лабораторная работа №4��$	��611��$	��809�� � 
ResizeMode$ 	CanResize=�.��� .+��� -    ��Name$ 
tabControl��.@��� $��1 задание����Z� .��� 
�������.+��� -    ��Name$ 	textBlock��$
��Left=�$��	46,33,0,0q�$��ProcessorArchitecture��$
��Wrap=�$	��Top=��� -   $ textBlock_Copy��$
��Left=�$��	46,87,0,0q�$��PageSize��$
��Wrap=�$	��Top=��� -   $ textBlock_Copy1��$
��Left=�$��	46,54,0,0q�$C��=Архитектура системы процессора.: ��$
��Wrap=�$	��Top=�$	��241��$��8(��� -   $ textBlock_Copy2��$
��Left=�$��
46,108,0,0q�$����Размер страницы и гранулярность страничной защиты и обязательства. Это размер страницы, используемый функцией VirtualAlloc.��$
��Wrap=�$	��Top=�$	��241��$��8(��� -   $ textBlock_Copy3��$
��Left=�$��
46,154,0,0q�$��MinimumApplicationAddress��$
��Wrap=�$	��Top=��� -   $ textBlock_Copy4��$
��Left=�$��
46,175,0,0q�$����Указатель на младший адрес памяти, доступный приложениям и библиотекам динамической компоновки (DLL).��$
��Wrap=�$	��Top=�$	��241��$��8(��� -	   $ textBlock_Copy5��$
��Left=�$��
46,207,0,0q�$��MaximumApplicationAddress��$
��Wrap=�$	��Top=��� -
   $ textBlock_Copy6��$
��Left=�$��
46,228,0,0q�$����Указатель на старший адрес памяти, доступный приложениям и библиотекам динамической компоновки (DLL).��$
��Wrap=�$	��Top=�$	��241��$��8(��� -   $ textBlock_Copy7��$
��Left=�$��
46,307,0,0q�$��ActiveProcessorMask��$
��Wrap=�$	��Top=��� -   $ textBlock_Copy8��$
��Left=�$��
46,328,0,0q�$����Маска, представляющая набор процессоров, сконфигурированных в системе. Нулевой бит – это процессор 0; 31 – это процессор номер 31.��$
��Wrap=�$	��Top=�$��8(�$��35��$	��241���� -   $ textBlock_Copy9��$
��Left=�$��
46,262,0,0q�$��NumberOfProcessors��$
��Wrap=�$	��Top=��� -   $ textBlock_Copy10��$
��Left=�$��
46,282,0,0q�$D��>Количество процессоров в системе.��$
��Wrap=�$	��Top=�$��8(��� -   $ textBlock_Copy11��$
��Left=�$��
431,33,0,0q�$��ProcessorType��$
��Wrap=�$	��Top=��� -   $ textBlock_Copy12��$
��Left=�$��
431,54,0,0q�$����Устаревший член, который оставлен для совместимости с Windows NT 3.5 и Windows Me/98/95. Используйте члены wProcessorArchitecture, wProcessorLevel, и wProcessorRevision для получения типа процессора.��$
��Wrap=�$	��Top=�$��8(�$	��242���� -   $ textBlock_Copy13��$
��Left=�$��432,112,0,0q�$��AllocationGranularity��$
��Wrap=�$	��Top=��� -   $ textBlock_Copy14��$
��Left=�$��432,133,0,0q�$����Гранулярность для начального адреса, в котором может быть выделена виртуальная память. Для получения большей информации, смотрите VirtualAlloc.��$
��Wrap=�$	��Top=�$	��242��$��8(��� -   $ textBlock_Copy15��$
��Left=�$��431,171,0,0q�$��ProcessorLevel��$
��Wrap=�$	��Top=��� -   $ textBlock_Copy16��$
��Left=�$��432,192,0,0q�$����Уровень архитектурно-зависимого прицессора системы. Это должно использоваться только для отображения соответствий. Для получения набора особенностей процессора, используйте функцию IsProcessorFeaturePresent.��$
��Wrap=�$	��Top=�$	��241��$��8(��� -   $ textBlock_Copy17��$
��Left=�$��431,252,0,0q�$��ProcessorRevision��$
��Wrap=�$	��Top=��� -   $ textBlock_Copy18��$
��Left=�$��431,268,0,0q�$����Ревизия архитектурно-зависимого процессора. Следующая таблица показывает, как значение ревизии подобрано к каждому типу архитектуры процессора.��$
��Wrap=�$	��Top=�$��8(�$	��242���� -    ��Name$ 
infolabel1��$��-��$
��Left=�$��
292,33,0,0q�$	��Top=�$
��Bold"�$��18(�$	��108��$��Center=�$��Center=����	#FF45AAF2��Z� �� -   $ 
infolabel2��$��-��$
��Left=�$��292,101,0,0q�$	��Top=�$
��Bold"�$��18(�$	��108��$��Center=����	#FF45AAF2�� -   $ 
infolabel3��$��-��$
��Left=�$��292,160,0,0q�$	��Top=�$
��Bold"�$��18(�$	��108��$��Center=�$��Center=����	#FF45AAF2�� -   $ 
infolabel4��$��-��$
��Left=�$��292,216,0,0q�$	��Top=�$
��Bold"�$��15(�$	��108��$��Center=�$��Center=����	#FF45AAF2�� -   $ 
infolabel5��$��-��$
��Left=�$��292,321,0,0q�$	��Top=�$
��Bold"�$��18(�$	��489��$��Center=�$��Center=����	#FF45AAF2�� -   $ 
infolabel6��$��-��$
��Left=�$��292,262,0,0q�$	��Top=�$
��Bold"�$��18(�$	��108��$��Center=�$��Center=����	#FF45AAF2�� -   $ 
infolabel7��$��-��$
��Left=�$��
678,33,0,0q�$	��Top=�$
��Bold"�$��18(�$	��103��$��Center=�$��Center=����	#FF45AAF2�� -   $ 
infolabel8��$��-��$
��Left=�$��678,113,0,0q�$	��Top=�$
��Bold"�$��18(�$	��103��$��Center=�$��Center=����	#FF45AAF2�� -   $ 
infolabel9��$��-��$
��Left=�$��678,181,0,0q�$	��Top=�$
��Bold"�$��18(�$	��103��$��Center=�$��Center=����	#FF45AAF2�� -    $ infolabel10��$��-��$
��Left=�$��678,260,0,0q�$	��Top=�$
��Bold"�$��18(�$	��103��$��Center=�$��Center=����	#FF45AAF2�� $��2 задание����Z� .��� 
�������.+�  LiveCharts.Wpf.Gauge  -!     Name$ uiTotalPhys��$��0��$��0��$��
93,269,0,0q�   Uses360Mode$ False��   From$ 0Q�	   To$	 100Q�   GaugeValue1	   Value#	 �   $
��Left=�$	��156��$	��100��$	��Top=��� -"   $ label��$.��(Загрузка физ. памяти, %��$
��Left=�$��
81,394,0,0q�$	��Top=�$��27��$	��180��
����������	#FF45AAF2$��Center=�$��Center=��� -#   $ textBlock_Copy19��$
��Left=�$��
93,431,0,0q�$��	TotalPhys��$
��Wrap=�$	��Top=�$��20��$	��207��
 � ToolTip$M
 GОбщий объем физической памяти в байтах���� -$   $ textBlock_Copy20��$
��Left=�$��
93,455,0,0q�$��	AvailPhys��$
��Wrap=�$	��Top=�$��18��$	��207��$U
 OОбъем доступной физической памяти в байтах���� -%   $ textBlock_Copy21��$
��Left=�$��540,431,0,0q�$��TotalPageFile��$
��Wrap=�$	��Top=�$��20��$	��201��$>
 8Размер файла подкачки в байтах���� -&   $ textBlock_Copy22��$
��Left=�$��540,454,0,0q�$��AvailPageFile��$
��Wrap=�$	��Top=�$��19��$	��201��$O
 IДоступный объем байтов в файле подкачки���� -'   $ textBlock_Copy23��$
��Left=�$��327,431,0,0q�$��TotalVirtual��$
��Wrap=�$	��Top=�$��18��$	��204��$O
 IОбщий объем виртуальной памяти в байтах���� -(   $ textBlock_Copy24��$
��Left=�$��327,455,0,0q�$��AvailVirtual��$
��Wrap=�$	��Top=�$��18��$	��204��$G
 AОбъем доступной виртуальной памяти���� -)   $ textBlock_Copy25��$
��Left=�$��327,478,0,0q�$��AvailExtendedVirtual��$
��Wrap=�$	��Top=�$��19��$	��204��$�
 �Объем незарезервированной памяти в расширенной части виртуальной памяти в байтах��  -*   $ uiTotalPhys_Copy��$��	0,271,0,0q�$ False��$ 0Q�$	 100Q�  GaugeValue2#	 �  $��Center=�$	��156��$	��102��$	��Top=�  -+   $ uiTotalPhys_Copy1��$��0��$��0��$��540,269,0,0q�$ False��$ 0Q�$	 100Q�  GaugeValue3#	 �  $
��Left=�$	��156��$	��100��$	��Top=��� -,   $ label_Copy2��$0��*Загрузка вирт. памяти, %��$��Center=�$��	0,393,0,0q�$	��Top=�$��28��$	��180��
����������	#FF45AAF2$��Center=�$��Center=��� --   $ label_Copy3��$5��/Загрузка файла подкачки, %��$
��Left=�$��528,393,0,0q�$	��Top=�$��28��$	��180��
����������	#FF45AAF2$��Center=�$��Center=�  -.   $ uiTotalPhys_Copy2��$��0��$��0,39,0,0q�$ False��$ 0Q�$	 100Q�  GaugeValue4#	 �  $��Center=�$	��248��$	��166��$	��Top=��� -/   $ 
label_Copy��$:��4Процент используемой памяти��$��Center=�$��	0,210,0,0q�$	��Top=�$��33��$	��298��
����������	#FF45AAF2$��Center=�$��Center=��� $
��Left=�$	��178��$��286,300,0,0q�$	��Top=�$��1�����	#FFCACACA J� RenderTransformOrigin$ 0.5,0.5&�z�V� .~���  �� ScaleX$ -1Q��� �� T� �� $
��Left=�$	��178��$��510,300,0,0q�$	��Top=�$��1�����	#FFCACACA$ 0.5,0.5&�z�V� .~��� $ -1Q��� �� T� �� $
��Left=�$��79��$��	22,26,0,0q����	#FF27AE60$	��Top=�$	��215���� -0   $ 
textBlock1��$
��Left=�$��	22,39,0,0q�$����Получение детальной информации о состоянии памяти компьютера с помощью GlobalMemoryStatus��$
��Wrap=�$	��Top=�$	��215��$��66�� �� Padding$ 7,7,7,7q�$��11(� �� TextAlignment$ Justify=��� -1   $ 
textBlock2��$
��Left=�$��	29,16,0,0q�$��Комментарий��$
��Wrap=�$	��Top=����	#FF27AE60
�������$��97��$ Center=�$ 0,2,0,0q�$��23���� $��3 задание����Z� .��� .+��� -2    ��Name$ 	listblock��$��0,55,0,0q�$y�Hidden=�&   System.Windows.Controls.DataGrid  -3     Name$ dataGrid��$��10,41,10,10q�   AutoGenerateColumns$
 True������ *
processmap+�� -4   $ label1��$C��=Название процесса (напр : uTorrent.exe): ��$
��Left=�$��	10,10,0,0q�$	��Top=��� -5    ��Name$ textBox��$
��Left=�$��
250,14,0,0q�$�� �� �� TextWrapping$
 Wrap=�$	��Top=�$	��120���� -6   $ label2��$�� ��$
��Left=�$��
375,10,0,0q�$	��Top=�