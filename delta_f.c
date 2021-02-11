/*******************************************************************************
 * Copyright (c) 2021 Willem Elbers (whe@willemelbers.com)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 ******************************************************************************/

/* Standard headers */
#include <stdio.h>
#include <sys/time.h>

/* Neutrino delta-f functions */
#include "delta_f.h"

/* Define the unit system and constants (Mpc, Gyr, 10^10 M_sol, Kelvin)*/
const struct internal_units units = {3.085678e+22, 3.153600e+16,
          1.988435e+40, 1.0
};
const struct phys_const phys_const = {3.063915e+02,  7.252438e-76,
          1.756589e-103, 8.416104e-72,
          1.951758,      1.681895e-04
};

int main() {

    /* Total number of neutrino particles */
    long long nr_nus = 256 * 256 * 256;

    /* Comoving physical sidelength of the box */
    double box_length = 256; // Mpc

    /* Compute the conversion factor from microscopic mass in electronvolts
     * to simulation particle mass in internal mass units */
    double mass_factor = neutrino_mass_factor(nr_nus, box_length, &phys_const);

    /* Prepare generating a particle */
    uint64_t id = 1000000; /* Particle id, used as random seed */
    double v[3];           /* Particle velocity */
    double x[3];           /* Particle position */
    double w;              /* Particle weight */
    double m_eV = 0.05;    /* Neutrino mass in electronvolts */

    printf("microscopic mass = %f eV\n", m_eV);
    printf("macroparticle mass = %f U_M\n\n", m_eV / mass_factor);

    /* Initialize the particle with a random position and velocity */
    init_neutrino_particle(id, m_eV, v, x, &w, box_length, &phys_const);

    /* Print some information about the particle */
    printf("Particle initialized with:\n");
    printf("x[3] = (%.3f, %.3f, %.3f) U_L\n", x[0], x[1], x[2]);
    printf("v[3] = (%.3f, %.3f, %.3f) U_L/U_t\n", v[0], v[1], v[2]);
    printf("weight = %e U_M\n\n", w);

    /* Update the velocity with a kick */
    v[0] *= 1.001;
    v[1] *= 0.999;
    v[2] *= 1.002;

    /* Update the particle weight */
    update_neutrino_particle(id, m_eV, v, x, &w, mass_factor, &phys_const);

    /* Print some information about the particle */
    printf("Particle state after update:\n");
    printf("x[3] = (%.3f, %.3f, %.3f) U_L\n", x[0], x[1], x[2]);
    printf("v[3] = (%.3f, %.3f, %.3f) U_L/U_t\n", v[0], v[1], v[2]);
    printf("weight = %e U_M\n", w);

    return 0;
}
