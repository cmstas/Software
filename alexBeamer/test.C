#include "alexBeamer.h"

void test(){

  pres myTest; 
  myTest.KeyColor("blue");
  myTest.Underline("Alex");
  myTest.TitleSlide("This is my Title Slide for this Great Presentation");

  //Second slide
  myTest.NewSlide();
  myTest.Title("This is my Awesome Second Slide with a Really Long Name.");
  myTest.FinishSlide();

  //Third slide
  myTest.NewSlide();
  myTest.FinishSlide();

}
