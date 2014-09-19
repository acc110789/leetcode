#include <vtkVersion.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderWindow.h>
#include <vtkSmartPointer.h>
#include <vtkChartXY.h>
#include <vtkTable.h>
#include <vtkPlot.h>
#include <vtkFloatArray.h>
#include <vtkContextView.h>
#include <vtkContextScene.h>
#include <vtkPen.h>

inline float fast_log2 (float val)                                                 
{                                                                                  
   int * const    exp_ptr = reinterpret_cast<int*>(&val);                          
   int            x = *exp_ptr;                                                    
   const int      log_2 = ((x << 23) & 255) - 128;                                 
   x &= ~(255 << 23);                                                              
   x += 127 << 23;                                                                 
   *exp_ptr = x;                                                                   
                                                                                   
   val = ((-1.0f/3) * val + 2) * val - 2.0f/3;   // (1)                            
                                                                                   
   return (val + log_2);                                                           
}                                                                                  
                                                                                   
inline float fast_log (const float &val)                                           
{                                                                                  
   return (fast_log2 (val) * 0.69314718f);                                         
}

int main(int, char *[])
{
  // Create a table with some points in it
  vtkSmartPointer<vtkTable> table = 
    vtkSmartPointer<vtkTable>::New();
 
  vtkSmartPointer<vtkFloatArray> arrX = 
    vtkSmartPointer<vtkFloatArray>::New();
  arrX->SetName("X Axis");
  table->AddColumn(arrX);
 
  vtkSmartPointer<vtkFloatArray> arrC = 
    vtkSmartPointer<vtkFloatArray>::New();
  arrC->SetName("Cosine");
  table->AddColumn(arrC);
 
  vtkSmartPointer<vtkFloatArray> arrS = 
    vtkSmartPointer<vtkFloatArray>::New();
  arrS->SetName("Sine");
  table->AddColumn(arrS);
 
  // Fill in the table with some example values
  int numPoints = 1024;
  double inc = 1.0 / (numPoints - 1);
  table->SetNumberOfRows(numPoints);
  for (int i = 0; i < numPoints; i++)
  {
    table->SetValue(i, 0, i * inc);
    table->SetValue(i, 1, log((1 + i) * inc));
    //table->SetValue(i, 2, pow(i * inc, 0.125));
  }
 
  // Set up the view
  vtkSmartPointer<vtkContextView> view = 
    vtkSmartPointer<vtkContextView>::New();
  view->GetRenderer()->SetBackground(1.0, 1.0, 1.0);
 
  // Add multiple line plots, setting the colors etc
  vtkSmartPointer<vtkChartXY> chart = 
    vtkSmartPointer<vtkChartXY>::New();
  view->GetScene()->AddItem(chart);
  vtkPlot *line = chart->AddPlot(vtkChart::LINE);
#if VTK_MAJOR_VERSION <= 5
  line->SetInput(table, 0, 1);
#else
  line->SetInputData(table, 0, 1);
#endif
  line->SetColor(0, 255, 0, 255);
  line->SetWidth(1.0);
  line = chart->AddPlot(vtkChart::LINE);
#if VTK_MAJOR_VERSION <= 5
  line->SetInput(table, 0, 2);
#else
  line->SetInputData(table, 0, 2);
#endif
  line->SetColor(255, 0, 0, 255);
  line->SetWidth(1.0);

  //view->GetRenderWindow()->SetMultiSamples(0);

  // Start interactor
  view->GetInteractor()->Initialize();
  view->GetInteractor()->Start();
 
  return EXIT_SUCCESS;
}
