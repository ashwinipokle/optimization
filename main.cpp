
#include <iostream>
#include <string>
using namespace std;

#include "DenseVector.h"
#include "SparseVector.h"
#include "textFileReader.h"
#include "Vector.h"
#include "VectoryFactory.h"
#include "TrainingInstance.h"
#include "stocGradDescUpdater.h"
#include "SquareLoss.h"
#include "naiveSGDOptimizer.h"
#include "PDL1RegUpdater.h"
#include "PDL1RegOptimizer.h"
#include "PDL2RegUpdater.h"
#include "PDL2RegOptimizer.h"
#include "PDL1BallUpdater.h"
#include "PDL1BallOptimizer.h"
#include "PDLinfUpdater.h"
#include "PDLinfOptimizer.h"
#include "CML1RegUpdater.h"
#include "CML1RegOptimizer.h"
#include "CML2RegOptimizer.h"
#include "CML2RegUpdater.h"
#include "CML1BallUpdater.h"
#include "CML1BallOptimizer.h"
#include "CMLinfRegUpdater.h"
#include "CMLinfRegOptimizer.h"
#include "RobustOptimizer.h"
#include "RobustUpdater.h"
#include "Norm.h"
#include "RobustLossFunction.h"
int main(){
	int inputType; //to decide type of DataFeeder
	double learningRate;
	int numFeatures;
	double epsilon = 0.01;
	int optType;
	int vectorType;
	int initVal = 1;
	string inputFile;
	int repetitions = 0;
	int timestep = 1;
	double delta,lambda,l1radius;
	double theta,threshold = 0;
	int normType,iterations = 0;
	std::cout<<"Choose Optimization type \n"<<
			" 1. Naive SGD \n"<<
			" 2. Primal Dual l1 Regularization \n"<<
			" 3. Primal Dual L1 Ball Projection \n"<<
			" 4. Primal Dual L2 Regularization \n"<<
			" 5. Primal Dual Linf Regularization \n"<<
			" 6. Composite Mirror Update L1 regularization \n"<<
			" 7. Composite Mirror Update L1 ball \n"<<
			" 8. Composite Mirror Update L2 regularization \n"<<
			" 9. Composite Mirror Update Linf REgularization \n"<<
			" 10. Robust Loss \n";
	std::cin>>optType;

	std::cout<<"Number of features : ";
	std::cin>>numFeatures;

	std::cout<<"Input Type \n"<<
		 "1.Data File \n";
	std::cin>>inputType;
	if(inputType == 1) { std::cout<<"Enter Data file name / path: "; std::cin>>inputFile;}

	std::cout<<"\n Vector Type : \n 0. Dense \n 1. Sparse : ";
	std::cin>>vectorType;

	std::cout<<"\n Enter timestep : ";
	std::cin>>timestep;

	std::cout<<"\n Enter repetitions :";
	std::cin>>repetitions;

	std::cout<<"\n Enter learning rate : ";
	std::cin>>learningRate;

	switch(optType)
	{
		//naiveStochasticGradient Descent
		case 1:
			if(inputType == 1){
				// all zero vector
				VectorPtr weight;
				LossFuncPtr mySquareLoss(new SquareLoss());
				if(vectorType == 0){
					DataFeederPtr myFileReader(new textFileReader(inputFile,numFeatures,Vector::DENSE));
					weight = createNewVector(Vector::DENSE, numFeatures, initVal);
					stocGradDescUpdater myUpdater(mySquareLoss, learningRate);
					std::shared_ptr<StochasticOptimizer> myOptimizer(new naiveSGDOptimizer(mySquareLoss,myFileReader, Vector::DENSE,numFeatures,learningRate,epsilon,timestep,repetitions));
					myOptimizer->optimize();
				}
				else
				{
					DataFeederPtr myFileReader(new textFileReader(inputFile,numFeatures,Vector::SPARSE));
					weight = createNewVector(Vector::SPARSE, numFeatures, initVal);
					stocGradDescUpdater myUpdater(mySquareLoss, learningRate);
					std::shared_ptr<StochasticOptimizer> myOptimizer(new naiveSGDOptimizer(mySquareLoss,myFileReader, Vector::SPARSE,numFeatures,learningRate,epsilon,timestep,repetitions));
					myOptimizer->optimize();
				}
			}
			break;
		case 2:
			std::cout<<"\nEnter optimization parameters: ";
			std::cout<<"\nEnter delta : ";
			std::cin>>delta;
			std::cout<<"\n Enter lambda : ";
			std::cin>>lambda;

			if(inputType == 1){
					VectorPtr weight;
					LossFuncPtr mySquareLoss(new SquareLoss());
					if(vectorType == 0){
						DataFeederPtr myFileReader(new textFileReader(inputFile,numFeatures,Vector::DENSE));
						weight = createNewVector(Vector::DENSE, numFeatures, initVal);
						PDL1RegUpdater myUpdater(mySquareLoss,Vector::DENSE,learningRate,delta,lambda,timestep,numFeatures);
						UpdaterPtr PDL1Updater = UpdaterPtr(new stocGradDescUpdater(mySquareLoss, learningRate));
						std::shared_ptr<StochasticOptimizer> myOptimizer(new PDL1RegOptimizer(mySquareLoss,myFileReader, Vector::DENSE,numFeatures,learningRate,delta, lambda,epsilon,timestep,repetitions));
						myOptimizer->optimize();
						myOptimizer->getWeight().print();
					}
					else
					{//sparse vector case
						DataFeederPtr myFileReader(new textFileReader(inputFile,numFeatures,Vector::SPARSE));
						weight = createNewVector(Vector::SPARSE, numFeatures, initVal);
						PDL1RegUpdater myUpdater(mySquareLoss,Vector::SPARSE,learningRate,delta,lambda,timestep,numFeatures);
						UpdaterPtr PDL1Updater = UpdaterPtr(new stocGradDescUpdater(mySquareLoss, learningRate));
						std::shared_ptr<StochasticOptimizer> myOptimizer(new PDL1RegOptimizer(mySquareLoss,myFileReader, Vector::SPARSE,numFeatures,learningRate,delta, lambda,epsilon,timestep,repetitions));
						myOptimizer->optimize();
						myOptimizer->getWeight().print();
					}
				}
				break;
		case 3:
			std::cout<<"\nEnter optimization parameters: ";
			std::cout<<"\nEnter delta : ";
			std::cin>>delta;
			std::cout<<"\nEnter l1 ball radius : ";
			std::cin>>l1radius;
			std::cout<<"\nEnter epsilon : ";
			std::cin>>epsilon;

		if(inputType == 1){
			LossFuncPtr mySquareLoss(new SquareLoss());
			// all zero vector
			VectorPtr weight;
			if(vectorType == 0)
			{
				DataFeederPtr myFileReader(new textFileReader(inputFile,numFeatures,Vector::DENSE));
				weight = createNewVector(Vector::DENSE, numFeatures, initVal);
				PDL1BallUpdater myUpdater(mySquareLoss,Vector::DENSE,learningRate,delta,l1radius,timestep,numFeatures);
				std::shared_ptr<StochasticOptimizer> myOptimizer(new PDL1BallOptimizer(mySquareLoss,myFileReader, Vector::DENSE,numFeatures,learningRate,delta,l1radius,epsilon,timestep,repetitions));
				myOptimizer->optimize();
			}
			else
			{
				//sparse vector case
				DataFeederPtr myFileReader(new textFileReader(inputFile,numFeatures,Vector::SPARSE));
				weight = createNewVector(Vector::SPARSE, numFeatures, initVal);
				PDL1BallUpdater myUpdater(mySquareLoss,Vector::SPARSE,learningRate,delta,l1radius,timestep,numFeatures);
				std::shared_ptr<StochasticOptimizer> myOptimizer(new PDL1BallOptimizer(mySquareLoss,myFileReader, Vector::SPARSE,numFeatures,learningRate,delta,l1radius,epsilon,timestep,repetitions));
				myOptimizer->optimize();
			}
		}
		break;

		case 4:
			std::cout<<"\nEnter optimization parameters: ";
			std::cout<<"\nEnter delta : ";
			std::cin>>delta;
			std::cout<<"\n Enter lambda : ";
			std::cin>>lambda;
			std::cout<<"\nEnter epsilon : ";
			std::cin>>epsilon;

			if(inputType == 1){
				LossFuncPtr mySquareLoss(new SquareLoss());
				VectorPtr weight;

				if(vectorType == 0){
					weight = createNewVector(Vector::DENSE, numFeatures, initVal);
					DataFeederPtr myFileReader(new textFileReader(inputFile,numFeatures,Vector::DENSE));
					PDL2RegUpdater myUpdater(mySquareLoss,Vector::DENSE,learningRate,delta,lambda,epsilon,timestep,numFeatures);
					std::shared_ptr<StochasticOptimizer> myOptimizer(new PDL2RegOptimizer(mySquareLoss,myFileReader, Vector::DENSE,numFeatures,learningRate,delta,lambda,epsilon,timestep,repetitions));
					myOptimizer->optimize();
				}
				else
				{//sparse vector case
					weight = createNewVector(Vector::SPARSE, numFeatures, initVal);
					DataFeederPtr myFileReader(new textFileReader(inputFile,numFeatures,Vector::SPARSE));
					PDL2RegUpdater myUpdater(mySquareLoss,Vector::SPARSE,learningRate,delta,lambda,epsilon,timestep,numFeatures);
					std::shared_ptr<StochasticOptimizer> myOptimizer(new PDL2RegOptimizer(mySquareLoss,myFileReader, Vector::SPARSE,numFeatures,learningRate,delta,lambda,epsilon,timestep,repetitions));
					myOptimizer->optimize();
				}
			}
			break;
		case 5:
				std::cout<<"\nEnter optimization parameters: ";
				std::cout<<"\nEnter delta : ";
				std::cin>>delta;
				std::cout<<"\n Enter lambda : ";
				std::cin>>lambda;
				std::cout<<"\nEnter epsilon : ";
				std::cin>>epsilon;
				if(inputType == 1){
				LossFuncPtr mySquareLoss(new SquareLoss());
				VectorPtr weight;

				if(vectorType == 0){
						weight = createNewVector(Vector::DENSE, numFeatures, initVal);
						DataFeederPtr myFileReader(new textFileReader(inputFile,numFeatures,Vector::DENSE));
						PDLinfUpdater myUpdater(mySquareLoss,Vector::DENSE,learningRate,delta,lambda,epsilon,timestep,numFeatures);
						std::shared_ptr<StochasticOptimizer> myOptimizer(new PDLinfOptimizer(mySquareLoss,myFileReader, Vector::DENSE,numFeatures,learningRate,delta,lambda,epsilon,timestep,repetitions));
						myOptimizer->optimize();
				}
				else
				{//sparse vector case
						weight = createNewVector(Vector::SPARSE, numFeatures, initVal);
						DataFeederPtr myFileReader(new textFileReader(inputFile,numFeatures,Vector::SPARSE));
						PDLinfUpdater myUpdater(mySquareLoss,Vector::SPARSE,learningRate,delta,lambda,epsilon,timestep,numFeatures);
						std::shared_ptr<StochasticOptimizer> myOptimizer(new PDLinfOptimizer(mySquareLoss,myFileReader, Vector::SPARSE,numFeatures,learningRate,delta,lambda,epsilon,timestep,repetitions));
						myOptimizer->optimize();
				}
				}
				break;
		case 6:
				std::cout<<"\nEnter optimization parameters: ";
				std::cout<<"\nEnter delta : ";
				std::cin>>delta;
				std::cout<<"\n Enter lambda : ";
				std::cin>>lambda;
				std::cout<<"\nEnter epsilon : ";
				std::cin>>epsilon;
				if(inputType == 1){
				LossFuncPtr mySquareLoss(new SquareLoss());
				VectorPtr weight;
				if(vectorType == 0){
						weight = createNewVector(Vector::DENSE, numFeatures, initVal);
						DataFeederPtr myFileReader(new textFileReader(inputFile,numFeatures,Vector::DENSE));
						CML1RegUpdater myUpdater(mySquareLoss,Vector::DENSE,learningRate,delta,lambda,epsilon,timestep,numFeatures);
						std::shared_ptr<StochasticOptimizer> myOptimizer(new CML1RegOptimizer(mySquareLoss,myFileReader, Vector::DENSE,numFeatures,learningRate,delta,lambda,epsilon,timestep,repetitions));
						myOptimizer->optimize();
						}
						else
						{//sparse vector case
						weight = createNewVector(Vector::SPARSE, numFeatures, initVal);
						DataFeederPtr myFileReader(new textFileReader(inputFile,numFeatures,Vector::SPARSE));
						CML1RegUpdater myUpdater(mySquareLoss,Vector::SPARSE,learningRate,delta,lambda,epsilon,timestep,numFeatures);
						std::shared_ptr<StochasticOptimizer> myOptimizer(new CML1RegOptimizer(mySquareLoss,myFileReader, Vector::SPARSE,numFeatures,learningRate,delta,lambda,epsilon,timestep,repetitions));
						myOptimizer->optimize();
						}
					}
				break;
		case 7:
					std::cout<<"\nEnter optimization parameters: ";
					std::cout<<"\nEnter delta : ";
					std::cin>>delta;
					std::cout<<"\n Enter l1 ball radius : ";
					std::cin>>l1radius;
					std::cout<<"\nEnter epsilon : ";
					std::cin>>epsilon;
					if(inputType == 1){
							LossFuncPtr mySquareLoss(new SquareLoss());
							// all zero vector
							VectorPtr weight;
							if(vectorType == 0)
							{
								DataFeederPtr myFileReader(new textFileReader(inputFile,numFeatures,Vector::DENSE));
								weight = createNewVector(Vector::DENSE, numFeatures, initVal);
								CML1BallUpdater myUpdater(mySquareLoss,Vector::DENSE,learningRate,delta,l1radius,timestep,numFeatures);
								std::shared_ptr<StochasticOptimizer> myOptimizer(new CML1BallOptimizer(mySquareLoss,myFileReader, Vector::DENSE,numFeatures,learningRate,delta,l1radius,epsilon,timestep,repetitions));
								myOptimizer->optimize();
							}
							else
							{
								//sparse vector case
								DataFeederPtr myFileReader(new textFileReader(inputFile,numFeatures,Vector::SPARSE));
								weight = createNewVector(Vector::SPARSE, numFeatures, initVal);
								CML1BallUpdater myUpdater(mySquareLoss,Vector::SPARSE,learningRate,delta,l1radius,timestep,numFeatures);
								std::shared_ptr<StochasticOptimizer> myOptimizer(new CML1BallOptimizer(mySquareLoss,myFileReader, Vector::SPARSE,numFeatures,learningRate,delta,l1radius,epsilon,timestep,repetitions));
								myOptimizer->optimize();
							}
					}break;
		case 8:
					std::cout<<"\nEnter optimization parameters: ";
					std::cout<<"\nEnter delta : ";
					std::cin>>delta;
					std::cout<<"\n Enter lambda : ";
					std::cin>>lambda;
					std::cout<<"\nEnter epsilon : ";
					std::cin>>epsilon;

					if(inputType ==1){
						LossFuncPtr mySquareLoss(new SquareLoss());
						VectorPtr weight;

					if(vectorType == 0){
							weight = createNewVector(Vector::DENSE, numFeatures, initVal);
							DataFeederPtr myFileReader(new textFileReader(inputFile,numFeatures,Vector::DENSE));
							CML2RegUpdater myUpdater(mySquareLoss,Vector::DENSE,learningRate,delta,lambda,epsilon,timestep,numFeatures);
							std::shared_ptr<StochasticOptimizer> myOptimizer(new CML2RegOptimizer(mySquareLoss,myFileReader, Vector::DENSE,numFeatures,learningRate,delta,lambda,epsilon,timestep,repetitions));
							myOptimizer->optimize();
						}
						else
						{//sparse vector case
							weight = createNewVector(Vector::SPARSE, numFeatures, initVal);
							DataFeederPtr myFileReader(new textFileReader(inputFile,numFeatures,Vector::SPARSE));
							CML2RegUpdater myUpdater(mySquareLoss,Vector::SPARSE,learningRate,delta,lambda,epsilon,timestep,numFeatures);
							std::shared_ptr<StochasticOptimizer> myOptimizer(new CML2RegOptimizer(mySquareLoss,myFileReader, Vector::SPARSE,numFeatures,learningRate,delta,lambda,epsilon,timestep,repetitions));
							myOptimizer->optimize();
						}
					}
					break;

		case 9:
				std::cout<<"\nEnter optimization parameters: ";
				std::cout<<"\nEnter delta : ";
				std::cin>>delta;
				std::cout<<"\n Enter lambda : ";
				std::cin>>lambda;
				std::cout<<"\nEnter epsilon : ";
				std::cin>>epsilon;


				if(inputType ==1){
					LossFuncPtr mySquareLoss(new SquareLoss());
					VectorPtr weight;

				if(vectorType == 0){
						weight = createNewVector(Vector::DENSE, numFeatures, initVal);
						DataFeederPtr myFileReader(new textFileReader(inputFile,numFeatures,Vector::DENSE));
						CMLinfRegUpdater myUpdater(mySquareLoss,Vector::DENSE,learningRate,delta,lambda,epsilon,timestep,numFeatures);
						std::shared_ptr<StochasticOptimizer> myOptimizer(new CMLinfRegOptimizer(mySquareLoss,myFileReader, Vector::DENSE,numFeatures,learningRate,delta,lambda,epsilon,timestep,repetitions));
						myOptimizer->optimize();
					}
					else
					{//sparse vector case
						weight = createNewVector(Vector::SPARSE, numFeatures, initVal);
						DataFeederPtr myFileReader(new textFileReader(inputFile,numFeatures,Vector::SPARSE));
						CMLinfRegUpdater myUpdater(mySquareLoss,Vector::SPARSE,learningRate,delta,lambda,epsilon,timestep,numFeatures);
						std::shared_ptr<StochasticOptimizer> myOptimizer(new CMLinfRegOptimizer(mySquareLoss,myFileReader, Vector::SPARSE,numFeatures,learningRate,delta,lambda,epsilon,timestep,repetitions));
						myOptimizer->optimize();
					}
				}
				break;
		case 10:
			std::cout<<"\nEnter optimization parameters: ";
				std::cout<<"\nEnter theta : ";
				std::cin>>theta;
				std::cout<<"\n Enter threshold : ";
				std::cin>>threshold;
				//std::cout<<"\nEnter epsilon : ";
				//std::cin>>epsilon;
				epsilon = 0.002;
				std::cout<<"\n Enter non adptive iterations : ";
				std::cin>>iterations;
				//std::cout<<"\n Enter norm : ";
				//std::cin>>normType;
				normType = 2;
				if(inputType ==1){
					LossFuncPtr myRobustLoss(new RobustLossFunction());
					VectorPtr weight;
					std::cout<<"Inside if";
					if(vectorType == 0){
						std::cout<<"Here!";
						weight = createNewVector(Vector::DENSE, numFeatures, initVal);
						weight->print();
						DataFeederPtr myFileReader(new textFileReader(inputFile,numFeatures,Vector::DENSE));
						RobustUpdater myUpdater(myRobustLoss,Vector::DENSE,learningRate,timestep,numFeatures);
						std::shared_ptr<StochasticOptimizer> myOptimizer(new RobustOptimizer(myRobustLoss,myFileReader, Vector::DENSE,numFeatures,learningRate,epsilon,timestep,repetitions,theta,threshold,iterations,normType));
						myOptimizer->optimize();
						}
		/*						else
								{//sparse vector case
									weight = createNewVector(Vector::SPARSE, numFeatures, initVal);
									DataFeederPtr myFileReader(new textFileReader(inputFile,numFeatures,Vector::SPARSE));
									CMLinfRegUpdater myUpdater(mySquareLoss,Vector::SPARSE,learningRate,delta,lambda,epsilon,timestep,numFeatures);
									std::shared_ptr<StochasticOptimizer> myOptimizer(new CMLinfRegOptimizer(mySquareLoss,myFileReader, Vector::SPARSE,numFeatures,learningRate,delta,lambda,epsilon,timestep,repetitions));
									myOptimizer->optimize();
								}*/
					}
	}
	system("pause");
	return 0;
}
