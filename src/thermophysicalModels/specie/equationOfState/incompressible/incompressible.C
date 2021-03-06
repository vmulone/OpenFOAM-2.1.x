/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2011 OpenFOAM Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

\*---------------------------------------------------------------------------*/

#include "incompressible.H"
#include "IOstreams.H"

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::incompressible::incompressible(Istream& is)
:
    specie(is),
    rho_(readScalar(is))
{
    is.check("incompressible::incompressible(Istream& is)");
}


Foam::incompressible::incompressible(const dictionary& dict)
:
    specie(dict),
    rho_(readScalar(dict.subDict("equationOfState").lookup("rho")))
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void Foam::incompressible::write(Ostream& os) const
{
    specie::write(os);

    dictionary dict("equationOfState");
    dict.add("rho", rho_);

    os  << indent << dict.dictName() << dict;
}


// * * * * * * * * * * * * * * * Ostream Operator  * * * * * * * * * * * * * //

Foam::Ostream& Foam::operator<<(Ostream& os, const incompressible& ico)
{
    os  << static_cast<const specie&>(ico)
        << token::SPACE << ico.rho_;

    os.check("Ostream& operator<<(Ostream& os, const incompressible& ico)");
    return os;
}


// ************************************************************************* //
