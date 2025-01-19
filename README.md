# FADIP: Lightweight Publish/Subscribe for Mobile Ad Hoc Networks (MANETs)

This repository contains an implementation of the **FADIP** protocol, based on the paper:

> **"FADIP: Lightweight Publish/Subscribe for Mobile Ad Hoc Networks"**
> *Koosha Paridel, Yves Vanrompay, Yolande Berbers.*
> Presented at the OTM 2010 International Conferences.

The implementation is built using [OMNeT++](https://omnetpp.org/), a discrete-event simulation environment.

## Overview

FADIP is a decentralized and lightweight **publish/subscribe** protocol designed for **Mobile Ad Hoc Networks (MANETs)**. It focuses on:
- **Efficient message routing** in dynamic, decentralized environments.
- **Scalability** by leveraging a topic-based communication model.
- **Adaptability** to frequent network topology changes inherent to MANETs.

### Note
The original implementation of the FADIP protocol described in the paper is not publicly available. This repository provides an implementation based on the descriptions and methodologies outlined in the paper.

## Features

- Implements the FADIP protocol to enable topic-based publish/subscribe communication.
- Simulates dynamic MANET scenarios using OMNeT++.
- Evaluates protocol performance under various network conditions.
- Visualizes network behavior and message propagation.

## Installation

### Prerequisites
1. **OMNeT++**: Version 6.0 or later is required. [Installation Guide](https://omnetpp.org/documentation/)
2. **INET Framework**: For MANET simulation support.

### Steps
1. Clone this repository:
   ```bash
   git clone https://github.com/Mohelm97/fadip-omnetpp6.git
   cd fadip-omnetpp6
   ```
2. Open the project in the OMNeT++ IDE.
3. Add the INET Framework as a dependency in your project configuration.
4. Build the project using the OMNeT++ IDE.

## Usage

1. Open the `.ini` configuration files to define simulation parameters such as:
   - Number of nodes.
   - Mobility model (random walk, Gauss-Markov, etc.).
   - Simulation time.

2. Run the simulation from the OMNeT++ IDE.

3. Analyze the results using OMNeT++'s built-in tools for visualization and performance evaluation.

## File Structure

- **/src**: Core implementation of the FADIP protocol.
- **/simulations**: Predefined scenarios and configuration files for testing.
- **/results**: Logs and performance metrics from simulations.

## Evaluation

This implementation measures key performance metrics, including:
- Message delivery rate.
- Overhead (network and computational).
- Scalability with varying node density.
- Adaptability to mobility patterns.

## Citation

If you use this implementation in your research, please cite the original paper:

```bibtex
@inproceedings{paridel2010fadip,
  title={Fadip: Lightweight publish/Subscribe for mobile ad hoc networks},
  author={Paridel, Koosha and Vanrompay, Yves and Berbers, Yolande},
  booktitle={On the Move to Meaningful Internet Systems, OTM 2010: Confederated International Conferences: CoopIS, IS, DOA and ODBASE, Hersonissos, Crete, Greece, October 25-29, 2010, Proceedings, Part II},
  pages={798--810},
  year={2010},
  organization={Springer}
}
```

## Contributing

Contributions, bug reports, and feature requests are welcome! Please open an issue or submit a pull request.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.  
