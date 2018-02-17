Attribute VB_Name = "Module5"
Sub tstSCI()
'
' tspSCI Macro
' Sorts and plots TST S and C funds for any file (calls the File Open dialog window)
'

'
'   so far it works exactly like macro tspmac
'
    Dim MyFile As String
    MyFile = Application.GetOpenFilename()
    Dim Book As Workbook
    Workbooks.Open (MyFile)
    ' MsgBox ActiveWorkbook.Name    ' show the workbook name in the pop-up window
    
    Range("A2:A200").Select
    ActiveWorkbook.Worksheets(ActiveWorkbook.Name).Sort.SortFields.Clear
    ActiveWorkbook.Worksheets(ActiveWorkbook.Name).Sort.SortFields.Add _
        Key:=Range("A2"), SortOn:=xlSortOnValues, Order:=xlAscending, DataOption _
        :=xlSortNormal
    With ActiveWorkbook.Worksheets(ActiveWorkbook.Name).Sort
        .SetRange Range("A2:G200")
        .Header = xlGuess
        .MatchCase = False
        .Orientation = xlTopToBottom
        .SortMethod = xlPinYin
        .Apply
    End With
    
    Range("A2:A200,F2:F200").Select
    Range("F2").Activate
    ActiveSheet.Shapes.AddChart.Select
    ActiveChart.ChartType = xlLineMarkers
    ' ActiveChart.Legend.Delete
    
    Range("A2:A200,D2:D200").Select
    Range("D2").Activate
    ActiveSheet.Shapes.AddChart.Select
    ActiveChart.ChartType = xlLineMarkers
    ' ActiveChart.Legend.Delete
    
    Range("A2:A200,E2:E200").Select
    Range("E2").Activate
    ActiveSheet.Shapes.AddChart.Select
    ActiveChart.ChartType = xlLineMarkers
    ' ActiveChart.Legend.Delete
    
    ' ActiveChart.SeriesCollection(1).MarkerForegroundColor = RGB(255, 0, 0)
    ' ActiveChart.SeriesCollection(1).Points(1).Interior.ColorIndex = 6
    ' ActiveChart.SetSourceData Source:=Range( _
        "ActiveWorkbook.Name!$A$2:$A$200,ActiveWorkbook.Name!$E$2:$E$200" _
        )
End Sub

