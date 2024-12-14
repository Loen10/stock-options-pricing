package main

import (
	"fmt"
	"math"
)

type BlackScholesMerton struct {
	underlyingPrice      float64
	strikePrice          float64
	volatility           float64
	riskFreeInterestRate float64
	dividendYield        float64
	yearsToExpiration    float64
}

func (x BlackScholesMerton) callPrice() float64 {
	d1 := (math.Log(x.underlyingPrice/x.strikePrice) + x.yearsToExpiration*
		(x.riskFreeInterestRate-
			x.dividendYield+x.volatility*x.volatility/2)) /
		(x.volatility * math.Sqrt(x.yearsToExpiration))

	d2 := d1 - x.volatility*math.Sqrt(x.yearsToExpiration)
	return x.underlyingPrice*
		math.Exp(-x.dividendYield*x.yearsToExpiration)*phi(d1) -
		x.strikePrice*math.Exp(-x.riskFreeInterestRate*x.yearsToExpiration)*
			phi(d2)
}

func main() {
	fmt.Println("STOCK OPTIONS")
	var params BlackScholesMerton

	read(&params.underlyingPrice, "Underlying price: ")
	read(&params.strikePrice, "Strike price: ")
	read(&params.volatility, "Volatility: ")
	read(&params.riskFreeInterestRate, "Risk-free interest rate: ")
	read(&params.dividendYield, "Dividend yield: ")
	read(&params.yearsToExpiration, "Years to expiration: ")

	fmt.Print(params.callPrice())
}

func read(x any, label string) error {
	fmt.Print(label)
	_, err := fmt.Scan(x)
	return err
}

func phi(x float64) float64 {
	return 0.5 * (1 + math.Erf(x/math.Sqrt2))
}
